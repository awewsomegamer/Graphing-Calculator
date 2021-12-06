#include "../../include/Graph/Graph.h"
#include "../../include/Log.h"
#include "../../include/Interpreter.h"

using namespace std;

Interpreter i;
int total_x = 10;
int total_y = 10;

Graph::Graph(){
	i = Interpreter();
}

void Graph::update(int w, int h){
	total_x = w/100;
	total_y = h/100;
}

Graph::Point Graph::get_point(string f, int x){
	string ff = "x = ";
	ff += to_string(x);
	ff += "\n";
	ff += f;

	i.run_line(ff);

	lua_getglobal(i.get_state(), "y");

	int y = 0;

	if (lua_isnumber(i.get_state(), -1)){
		y = lua_tonumber(i.get_state(), -1);
	}

	Graph::Point p = {x,y};

	return p;
}


