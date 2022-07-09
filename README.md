# pomocpp
## Introduction
pomocpp is a small, simple, terminal-based pomodoro timer for Linux users to assist those following the pomodoro technique for studying, work, or any other type of activity. The user is able to freely set the study/work time, break time, and the amount of sets. A typical study time is 25 minutes with a break of 5-10 minutes, though some users opt for the more intensive 60 minute study with a 15 minute break. 

## Compilation
pomocpp requires a compiler with C++17 support, libsqlite3-dev libraries, libnotify-bin (for `notify-send`), and CMake. Once the dependencies have been satisfied, compilation can be done as follows:

```
$ mkdir build && cd build
$ cmake ..
$ make -j$(nproc)
```

The program can then be executed:
```
$ ./pomocpp
```

## Usage
When attempting to execute the program, the user should be prompted with the various options and their use. An example output:
```
pomocpp - a basic pomodoro timer written in cpp.
Usage: ./pomocpp <options>
Available options:
	s, start <id> - starts the given pomodoro session
	c, create <name> <time> <break_time> <count> - creates a new pomodoro
	d, del <id> - deletes the specified pomodoro
	l, list - lists created pomodoros
```

For example, to create a pomodoro with a timer of 25 minutes and a break time of 10 minutes that repeats 3 times, one would run the following:
```
./pomocpp c CompSci 0.25 0.1 3
Successfully created new pomodoro 'CompSci'.
```

The user is then able to see their newly created pomodoro with the `list` option:
```
./pomocpp list
1: [CompSci] - [T0.25m] - [B0.1m] - [3x]
```

They can then start the session using the `start` option with the desired pomodoro's ID:
```
./pomocpp s 1
```

All saved pomodoros can be inspected using SQLite3 on the database file at ~/.config/pomocpp/database.pcp.

## Screenshots
![Pomodoro Session](/images/pomocpp-session.png)
Example of a pomodoro session taking place. After the time has elapsed, a notification is sent and the break time is started. Once the break time has concluded, another notification is sent and the user is given the option to either continue or quit, using the c and q keys respectively.
