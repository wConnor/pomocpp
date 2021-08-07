#include <chrono>
#include <thread>
#include <iomanip>
#include <ncurses.h>
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
	/* moves arguments from c-style argv array into a c++ vector
	   for ease of use. */
	std::vector<std::string> args;
	for (int i = 0; i != argc; ++i) {
		args.push_back(static_cast<std::string>(argv[i]));
	}

	/* checks whether or not the user has supplied an argument
	   when executing the program. */
	if (argc >= 2) {
		Database db;
		if (args[1] == "start") {
			if (argc >= 3) {
				/* try-catch statement necessary due to use of std::stoi */
				try {
					Pomodoro pomo = db.get_pomo(std::stoi(args[2]));

					/* checks whether or not a pomo has actually been
					   retrieved; name should not be empty. */
					if (pomo.get_name() != "") {
						char choice = 'c';
						int time_remaining = pomo.get_time() * 60;
						int *time_ptr = &time_remaining;
						initscr();
						noecho();
						std::thread char_poll([&choice, time_ptr](){
							choice = getch();
							std::this_thread::sleep_for(std::chrono::seconds(1));
							if (choice == 'q') {
								*time_ptr = 0;
							}
						});
						refresh();
						printw("*- %s: Time %f m, Break %f m, %i Times -*\n", pomo.get_name().c_str(), pomo.get_time(), pomo.get_break_time(), pomo.get_count());
						refresh();

						for (; time_remaining >= 0; --time_remaining) {
							printw("\rTime Remaining: %02d:%02d", time_remaining / 60, time_remaining % 60);
							refresh();
							std::this_thread::sleep_for(std::chrono::seconds(1));
						}
						char_poll.join();
					} else {
						std::cerr << "Invalid ID specified." << std::endl;
					}
				} catch (std::exception &e) {
					std::cerr << "ERROR: Invalid type specified." << std::endl;
					std::cout << "\t<id> must be an integer." << std::endl;
				}
			} else {
				std::cout << "Usage: " << args[0] << " start <id>" << std::endl;
			}

		} else if (args[1] == "create") {
			if (argc >= 6) {
				try {
					/* creates a Pomodoro object using the
					   specified arguments and writes it to the
					   sqlite database. if the user has input an invalid type as one of the arguments,
					   an exception is thrown. */
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
			std::vector<Pomodoro> pomos_list = db.get_all_pomos();

			for (auto &c : pomos_list) {
				std::cout << c.get_id() << ": "
						  << '[' << c.get_name() << "] - "
						  << "[T" << c.get_time() << "m] - "
						  << "[B" << c.get_break_time() << "m] - "
						  << '[' << c.get_count() << "x]" << std::endl;
			}
		} else {
			/* if the user has executed the program without arguments,
			   print the usage options. */
			usage(args[0]);
		}
	} else {
		usage(args[0]);
	}

	endwin();

	return 0;
}
