#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include "pomo.hpp"

void usage(std::string program_name)
{
	std::cout << "pomocpp - a basic pomodoro timer written in cpp." << std::endl;
	std::cout << "Usage: " << program_name << " <options>" << std::endl;
	std::cout << "Available options:" << std::endl;
	std::cout << "\tstart <name> - starts the given pomodoro session" << std::endl;
	std::cout << "\tcreate <name> <time> <break_time> <count> - creates a new pomodoro" << std::endl;
	std::cout << "\tdel <name> - deletes the specified pomodoro" << std::endl;
	std::cout << "\tlist - lists created pomodoros" << std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i != argc; ++i) {
		args.push_back(static_cast<std::string>(argv[i]));
	}

	if (argc >= 2) {
		if (args[1] == "start") {
			
		} else if (args[1] == "create") {
			
		} else if (args[1] == "del") {
			
		} else if (args[1] == "list") {
			
		} else {
			usage(args[0]);
		}

	} else {
		usage(args[0]);
	}
	
    return 0;
}
