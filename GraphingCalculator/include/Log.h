#pragma once

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>


enum type {
	ERROR,
	NORMAL,
	WARNING,
	FATAL
};

void log(std::string message, enum type t);

#endif
