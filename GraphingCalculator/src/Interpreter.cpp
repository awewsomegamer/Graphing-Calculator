#include "../include/Interpreter.h"
#include "../include/Log.h"

lua_State* L;

int draw_triangle(lua_State* L){
	glBegin(GL_TRIANGLES);
		glVertex2f(0,0.5);
		glColor3f(1,0,0);

		glVertex2f(0.125,0);
		glColor3f(0,1,0);

		glVertex2f(-0.125,0);
		glColor3f(0,0,1);
	glEnd();

	return 0;
}

Interpreter::Interpreter(){
	L = luaL_newstate();

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

}
