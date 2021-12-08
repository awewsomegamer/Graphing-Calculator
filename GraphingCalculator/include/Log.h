#pragma once

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

enum type{
	LERROR,
	LNORMAL,
	LWARNING,
	LFATAL
};

//enum type {
//	ERROR = 0,
//	NORMAL = 1,
//	WARNING = 2,
//	FATAL = 3
//}

void log(std::string message, type t);

#endif
