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
		std::ofstream db_file(db_path);
		std::cout << "Created pomocpp database file at " << db_path << '.' << std::endl;
		db_file.close();
	}
}

void Database::write_to_db(Pomodoro &pomo)
{
	try {
		std::ofstream db_file(db_path, std::ios_base::app);

		db_file << pomo.get_name() << "$=!"
				<< pomo.get_time() << "$=!"
				<< pomo.get_break_time() << "$=!"
				<< pomo.get_count() << std::endl;

		db_file.close();
		std::cout << "Successfully created new pomodoro \'" << pomo.get_name() << "'." << std::endl;

	} catch (std::exception &e) {
		std::cerr << "Failed to write to " << db_path << '.';
		std::cerr << e.what() << std::endl;
	}
}

std::vector<Pomodoro> Database::get_pomos()
{

	std::fstream db_file(db_path);
	std::string line;
	
	int line_counter = 0;

	std::vector<std::string> temp;
	std::vector<std::string> all_lines;

	while (std::getline(db_file, line)) {
		all_lines.push_back(line);

	}

	std::vector<Pomodoro> pomos;
	pomos.resize(all_lines.size());

	std::string delimiter = "$=!";
	size_t pos = 0;
	std::string token = "";

	for (auto &c : all_lines) {
		while ((pos = c.find(delimiter)) != std::string::npos) {
			token = c.substr(0, pos);
			temp.push_back(token);
			c.erase(0, pos + delimiter.length());
		}
		
		pomos[line_counter].set_id(line_counter + 1);
		pomos[line_counter].set_name(temp[0]);
		pomos[line_counter].set_time(std::stod(temp[1]));
		pomos[line_counter].set_break_time(std::stod(temp[2]));
		pomos[line_counter].set_count(std::stoi(c));

		temp.clear();		
		line_counter++;
	}

	return pomos;
}
