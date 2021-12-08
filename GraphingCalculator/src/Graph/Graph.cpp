#include "../../include/Graph/Graph.h"
#include "../../include/Log.h"
#include "../../include/Interpreter.h"

using namespace std;

double ct = .1;

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

void Graph::plot_smooth_lines(std::string function, int mode){
	glBegin(mode);
	for (int x = -total_x+1; x < total_x; x++){
		glColor3f(0,0,0);
		Graph::Point point = Graph::get_point(function, x);

		glVertex3d(x/ct, (double)(point.y/ct), 0);
	}
	glEnd();

	ct = 32.5;
}

void Graph::plot_rough_lines(std::string function){
	glBegin(GL_LINES);
	for (int x = -total_x+1; x < total_x; x++){
		glColor3f(0,0,0);
		Graph::Point point = Graph::get_point(function, x);

		glVertex3d(x/ct, (double)(point.y/ct), 0);
	}
	glEnd();

	ct = 32.5;
}


int Graph::get_total_x(){
	return total_x;
}

int Graph::get_total_y(){
	return total_y;
}

Graph::Point Graph::get_point(string f, double x){
	string ff = "x = ";
	ff += to_string(x);
	ff += "\n";
	ff += f;

	i.run_line(ff);

	lua_getglobal(i.get_state(), "y");

	double y = 0;

	if (lua_isnumber(i.get_state(), -1)){
		y = (double)lua_tonumber(i.get_state(), -1);
	}

	Graph::Point p = {x,y};

	return p;
}


