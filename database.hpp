#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include "pomo.hpp"

class Database
{
private:
	std::filesystem::path db_path;
	
public:
    Database();
	void write_to_db(Pomodoro &pomo);
	void delete_from_db(const int &id);
	std::vector<Pomodoro> get_pomos();
};

#endif
