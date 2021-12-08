#include "../include/Log.h"

std::string e_names[] = {"ERROR", "NORMAL", "WARNING", "FATAL"};

void log(std::string message, type t){
	std::cout << "[" << e_names[t] << "] " << message << std::endl;
}
