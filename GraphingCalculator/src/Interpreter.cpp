#include "../include/Interpreter.h"
#include "../include/Log.h"

lua_State* L;

int draw_triangle(lua_State* L){
	glBegin(GL_TRIANGLES);
		glVertex3f(0,0.5,0);
		glColor3f(1,0,0);

		glVertex3f(0.5,0,0);
		glColor3f(0,1,0);

		glVertex3f(-0.5,0,0);
		glColor3f(0,0,1);
	glEnd();

	return 0;
}

int factorial(lua_State* L){
	int number = lua_tonumber(L, -1);

	int fact = 1;

	for (int i = 1; i < number; i++){
		fact += fact * i;
	}

	lua_pushnumber(L, fact);

	return 1;
}

Interpreter::Interpreter(bool libs){
	L = luaL_newstate();
	if (libs) luaL_openlibs(L);

	// Register Lua functions here
	lua_register(L, "draw_triangle", &draw_triangle);
	lua_register(L, "factorial", &factorial);

}

bool validate(int result){
	if (result != LUA_OK){
		log(lua_tostring(L, -1), LERROR);
		return false;
	}

	return true;
}


void Interpreter::run_line(std::string line){
	if (validate(luaL_dostring(L, line.c_str()))){
//		log("Executed Lua <"+line+">", NORMAL);
	}
}

void Interpreter::run_file(std::string filename){
	if (validate(luaL_dofile(L, filename.c_str()))){
//		log("Executed Lua <"+filename+">", NORMAL);
	}
}

lua_State* Interpreter::get_state(){
	return L;
}
