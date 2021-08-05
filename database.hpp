#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include "pomo.hpp"

class Database
{
private:
	std::filesystem::path db_path;
	
public:
    Database();
	void write_to_db(Pomodoro &pomo);
};

#endif
