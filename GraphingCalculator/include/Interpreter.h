#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

extern "C"{
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}

class Interpreter{
public:
	Interpreter();

	void run_file(std::string file);
	void run_line(std::string line);
	lua_State* get_state();
};

#endif
