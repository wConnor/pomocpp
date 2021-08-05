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
