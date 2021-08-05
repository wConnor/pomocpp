#ifndef POMO_HPP
#define POMO_HPP

#include <string>

class Pomodoro
{
private:
	std::string name = "";
	double time = 0.0;
	double break_time = 0.0;
	int count = 0;

public:
	Pomodoro(std::string name, double time, double break_time, int count);

	std::string get_name();
	void set_name(std::string new_name);

	double get_time();
	void set_time(double new_time);

	double get_break_time();
	void set_break_time(double new_break_time);

	int get_count();
	void set_count(int new_count);
};

#endif
