#include "../include/Log.h"

// Names of errors sorted by index
std::string e_names[] = {"ERROR", "NORMAL", "WARNING", "FATAL"};

// Function that concatenates a given message and error type
void log(std::string message, type t){
	std::cout << "[" << e_names[t] << "] " << message << std::endl;
}
