#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

namespace LOG{

std::string e_names[] = {"ERROR", "NORMAL", "WARNING", "FATAL"};

enum type {
	ERROR,
	NORMAL,
	WARNING,
	FATAL
};


void log(std::string message, enum type t){
	std::cout << "[" << e_names[t] << "] " << message << std::endl;
}

}

#endif
