#include "database.hpp"

Database::Database() {
#ifdef _WIN32
	db_path = std::filesystem::current_path + std::filesytem::path::prefrred_separator + "pomocpp" + std::filesystem::path::preferred_separator + "database.pcp";
#elif defined __unix__
	db_path = std::string(std::getenv("HOME")) + std::filesystem::path::preferred_separator + ".config" + std::filesystem::path::preferred_separator + "pomocpp" + std::filesystem::path::preferred_separator + "database.pcp";
#elif defined __APPLE__
	db_path = std::string(std::getenv("HOME")) + std::filesystem::path::preferred_separator + ".config" + std::filesystem::path::preferred_separator + "pomocpp" + std::filesystem::path::preferred_separator + "database.pcp";
#endif

	if (!std::filesystem::exists(db_path.parent_path())) {
		std::filesystem::create_directory(db_path.parent_path());
		std::cout << "Created pomocpp directory at " << db_path.parent_path() << '.' << std::endl;
	}

	if (!std::filesystem::exists(db_path)) {
		sqlite3 *db;
		int res = sqlite3_open(db_path.c_str(), &db);
		std::string sql_query;

		if (res) {
			std::cerr << "Failed to create database at " << db_path << '.' << std::endl;
			std::cerr << "SQL error: " << sqlite3_errmsg(db);
		} else {
			sql_query = "CREATE TABLE POMOCPP (" \
				"id INTEGER PRIMARY KEY, " \
				"name TEXT NOT NULL, " \
				"time DOUBLE NOT NULL, " \
				"break_time DOUBLE NOT NULL, " \
				"count INTEGER NOT NULL);";

			res = sqlite3_exec(db, sql_query.c_str(), nullptr, 0, nullptr);

			if (res != SQLITE_OK) {
				std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			} else {
				std::cout << "Created pomocpp database at " << db_path << '.' << std::endl;
			}
		}
		sqlite3_close(db);
	}
}

void Database::write_to_db(Pomodoro &pomo)
{
	sqlite3 *db;
	int res = sqlite3_open(db_path.c_str(), &db);

	if (res) {
		std::cout << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
	} else {
		std::string sql_query = "INSERT INTO POMOCPP (NAME, TIME, BREAK_TIME, COUNT) "	\
			"VALUES ('" + pomo.get_name() + "', " + std::to_string(pomo.get_time()) + ", " + std::to_string(pomo.get_break_time()) + ", " + std::to_string(pomo.get_count()) + ");";
		res = sqlite3_exec(db, sql_query.c_str(), nullptr, 0, nullptr);

		if (res != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db);
		} else {
			std::cout << "Successfully created new pomodoro '" << pomo.get_name() << "'." << std::endl;
		}
	}
}

std::vector<Pomodoro> Database::get_pomos()
{
	std::vector<Pomodoro> pomos;
	sqlite3 *db;
	int res = sqlite3_open(db_path.c_str(), &db);

	if (res) {
		std::cerr << "Failed to open database at " << db_path << '.';
	} else {
		sqlite3_stmt *stmt;

		std::string sql_query = "SELECT * FROM POMOCPP;";
		res = sqlite3_prepare_v2(db, sql_query.c_str(), -1, &stmt, nullptr);

		if (res != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db);
		} else {
			while ((res = sqlite3_step(stmt)) == SQLITE_ROW) {
				pomos.push_back(Pomodoro(sqlite3_column_int(stmt, 0),
										 reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
										 sqlite3_column_double(stmt, 2),
										 sqlite3_column_double(stmt, 3),
										 sqlite3_column_int(stmt, 4)));
			}
			if (res != SQLITE_DONE) {
				std::cerr << "Failed to get pomos: " << sqlite3_errmsg(db) << std::endl;

			}
		}
	}

	return pomos;
}

void Database::delete_from_db(const int &id)
{
	sqlite3 *db;
	int res = sqlite3_open(db_path.c_str(), &db);

	if (res) {
		std::cerr << "Failed to open database at " << db_path << '.';
	} else {
		std::string sql_query = "DELETE FROM POMOCPP WHERE ID = " + std::to_string(id) + ";";
		res = sqlite3_exec(db, sql_query.c_str(), nullptr, 0, nullptr);

		if (res) {
			std::cerr << "Failed to remove pomo entry #" << id << '.' << std::endl;
			std::cerr << sqlite3_errmsg(db) << std::endl;
		} else {
			std::cout << "Deleted pomo entry #" << id << '.' << std::endl;
		}
	}
}
