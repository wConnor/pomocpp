#include <chrono>
#include <memory>
#include "database.hpp"

void usage(std::string program_name)
{
	std::cout << "pomocpp - a basic pomodoro timer written in cpp." << std::endl;
	std::cout << "Usage: " << program_name << " <options>" << std::endl;
	std::cout << "Available options:" << std::endl;
	std::cout << "\tstart <name> - starts the given pomodoro session" << std::endl;
	std::cout << "\tcreate <name> <time> <break_time> <count> - creates a new pomodoro" << std::endl;
	std::cout << "\tdel <id> - deletes the specified pomodoro" << std::endl;
	std::cout << "\tlist - lists created pomodoros" << std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i != argc; ++i) {
		args.push_back(static_cast<std::string>(argv[i]));
	}

	if (argc >= 2) {
		Database db;
		if (args[1] == "start") {

		} else if (args[1] == "create") {
			if (argc >= 6) {
				try {
					std::unique_ptr<Pomodoro> pomo = std::make_unique<Pomodoro>(args[2], std::stod(args[3]), std::stod(args[4]), std::stoi(args[5]));
					db.write_to_db(*pomo);
				} catch (std::exception &e) {
					std::cerr << "ERROR: Invalid type specified." << std::endl;
					std::cerr << "\t<time>, <break_time>, and <count> must be numbers." << std::endl;
				}
			} else {
				std::cout << "Usage: " << args[0] << " create <name> <time> <break_time> <count>" << std::endl;
			}
		} else if (args[1] == "del") {
			if (argc >= 3) {
				try {
					db.delete_from_db(std::stoi(args[2]));
				} catch (std::exception &e) {
					std::cerr << "ERROR: Invalid ID." << std::endl;
				}
			} else {
				std::cout << "Usage: " << args[0] << " del <id>" << std::endl;
			}

		} else if (args[1] == "list") {
			std::vector<Pomodoro> pomos_list = db.get_pomos();

			for (auto &c : pomos_list) {
				std::cout << c.get_id() << ": "
						  << '[' << c.get_name() << "] - "
						  << "[T" << c.get_time() << "m] - "
						  << "[B" << c.get_break_time() << "m] - "
						  << '[' << c.get_count() << "x]" << std::endl;
			}
		} else {
			usage(args[0]);
		}

	} else {
		usage(args[0]);
	}

	return 0;
}
