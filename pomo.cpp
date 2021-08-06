#include "pomo.hpp"

Pomodoro::Pomodoro() { };

Pomodoro::Pomodoro(std::string name, double time, double break_time, int count)
{
	this->name = name;
	this->time = time;
	this->break_time = break_time;
	this->count = count;
}

Pomodoro::Pomodoro(int id, std::string name, double time, double break_time, int count)
{
	this->id = id;
	this->name = name;
	this->time = time;
	this->break_time = break_time;
	this->count = count;
}

int Pomodoro::get_id() { return id; }
void Pomodoro::set_id(int new_id) { id = new_id; }

std::string Pomodoro::get_name() { return name; }
void Pomodoro::set_name(std::string new_name) { name = new_name; }

double Pomodoro::get_time() { return time; }
void Pomodoro::set_time(double new_time) { time = new_time; }

double Pomodoro::get_break_time() { return time; }
void Pomodoro::set_break_time(double new_break_time) { break_time = new_break_time; }

void Pomodoro::set_count(int new_count) { count = new_count; }
int Pomodoro::get_count() { return count; }
