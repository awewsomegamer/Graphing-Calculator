#include "../include/Interpreter.h"
#include "../include/Log.h"

// Lua virtual machine object
lua_State* L;

// This function can be called from lua to get the factorial of the given argument
int factorial(lua_State* L){
	int number = lua_tonumber(L, -1);

	int fact = 1;

	for (int i = 1; i < number; i++){
		fact += fact * i;
	}

	lua_pushnumber(L, fact);

	return 1;
}

// Create a Lua interpreter
Interpreter::Interpreter(bool libs){
	L = luaL_newstate();
	if (libs) luaL_openlibs(L);

	// Register Lua functions here
	lua_register(L, "factorial", &factorial);

}

// Log errors that may have occurred
bool validate(int result){
	if (result != LUA_OK){
		log(lua_tostring(L, -1), LERROR);
		return false;
	}

	return true;
}

// Run a simple string
void Interpreter::run_line(std::string line){
	validate(luaL_dostring(L, line.c_str()));
}

// Run a file
void Interpreter::run_file(std::string filename){
	validate(luaL_dofile(L, filename.c_str()));
}

// Getter for the virtual machine
lua_State* Interpreter::get_state(){
	return L;
}
