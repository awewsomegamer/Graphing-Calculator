#include "../include/Interpreter.h"
#include "../include/Log.h"

lua_State* L;

int draw_triangle(lua_State* L){
	glBegin(GL_TRIANGLES);
		glVertex3f(0,1,0.2);
		glColor3f(1,0,0);

		glVertex3f(1,0,0.2);
		glColor3f(0,1,0);

		glVertex3f(-1,0,0.2);
		glColor3f(0,0,1);
	glEnd();

	return 0;
}

Interpreter::Interpreter(){
	L = luaL_newstate();
	luaL_openlibs(L);

	// Register Lua functions here
	lua_register(L, "draw_triangle", &draw_triangle);
}

bool validate(int result){
	if (result != LUA_OK){
		log(lua_tostring(L, -1), ERROR);
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
