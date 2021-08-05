#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <filesystem>
#include <fstream>
#include <iostream>

class Database
{
private:
	std::filesystem::path db_path;
	
public:
    Database();

};

#endif
