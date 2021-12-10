#include "../../include/Graph/Graph.h"
#include "../../include/Log.h"
#include "../../include/Interpreter.h"
#include <math.h>

using namespace std;

double scale = 1;
const double fineness = 0.01;

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
	for (double x = -total_x+1; x < total_x; x+=fineness){
		Graph::Point point = Graph::get_point(function, x);

		glColor3f(x,point.y,0.5);
		glVertex3d(x, (double)(point.y), 0);
	}
	glEnd();
}

void Graph::plot_rough_lines(std::string function){
	glBegin(GL_LINES);
	for (double x = -total_x+1; x < total_x; x+=fineness){
		glColor3f(0.5,0.5,0.5);
		Graph::Point point = Graph::get_point(function, x);

		glVertex3d(x/scale, (double)(point.y/scale), 0);
	}
	glEnd();
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


