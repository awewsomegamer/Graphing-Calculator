#include "../../include/Graph/Graph.h"
#include "../../include/Log.h"
#include "../../include/Interpreter.h"
#include <math.h>
#include <iostream>
using namespace std;

double fineness = 0;
double scale = 1;
double cx = 0;
double cy = 0;

Interpreter i(true);
int total_x = 10;
int total_y = 10;

Graph::Graph(Config conf){
	fineness = conf.fineness;
}

void Graph::update(int w, int h, double s, double gx, double gy){
	total_x = w/100;
	total_y = h/100;
	scale = s;
	cx = gx;
	cy = gy;
}


//Add comfort features like x^2 = math.pow(x,2) or don't
//std::string comfortize(std::string string){
//
//
//	return "";
//}

bool Graph::check_render(Point p, int minimizer){
	// in GL everything starts at 1

	int width = 1;
	int height = 1;

	glBegin(GL_POINTS);
	for (double x = cx-width; x < cx+width; x+=0.1){
		for (double y = cy-height; y < cy+height; y+=0.1){
			glColor3f(0,1,1);
			glVertex3d(-x, -y, 0);
		}
	}
	glEnd();

	bool ret = false;

	if (-p.x >= cx-width && -p.x <= cx+width){
		if (-p.y >= cy-height && -p.y <= cy+height){
			ret = true;
		}
	}

	return ret;
}

void Graph::plot(std::string function, int mode){
	glBegin(mode);

//	for (double y = -total_y+1; y < total_y; y+=fineness*10){
		std::cout << scale << std::endl;
		for (double x = -cx-scale*2; x <= -cx+scale*2; x+=fineness){
//		for (double x = -total_x+1; x < total_x; x+=fineness){
			Graph::Point point = Graph::get_point(function, x, 0);

//			if (check_render(point, 1)){
				glColor3f(x,point.y, 0.5);
				glVertex3d(x, (double)(point.y), 0);
//			}
		}
//	}

	glEnd();
}


//
//void Graph::plot_rough_lines(std::string function){
//	glBegin(GL_LINES);
//	for (double x = -total_x+1; x < total_x; x+=fineness){
//		glColor3f(0.5,0.5,0.5);
//		Graph::Point point = Graph::get_point(function, (float)x);
//
//		glVertex3d(x/scale, (double)(point.y/scale), 0);
//	}
//	glEnd();
//}


int Graph::get_total_x(){
	return total_x;
}

int Graph::get_total_y(){
	return total_y;
}

Graph::Point Graph::get_point(string f, double x, double y){
	lua_pushnumber(i.get_state(), x);
	lua_setglobal(i.get_state(), "x");
	lua_pushnumber(i.get_state(), y);
	lua_setglobal(i.get_state(), "y");

	i.run_line(f);

	lua_getglobal(i.get_state(), "f");

	double result = 0;

	if (lua_isnumber(i.get_state(), -1)){
		result = (double)lua_tonumber(i.get_state(), -1);
	}

	lua_pop(i.get_state(), -1);

//	double colors[3];
//
//	lua_getglobal(i.get_state(), "c");
//	if (lua_istable(i.get_state(),-1)){
//		std::cout << lua_tonumber(i.get_state(), 1) <<
//				lua_tonumber(i.get_state(),1) <<
//				lua_tonumber(i.get_state(), 1) << std::endl;
//	}

	Graph::Point p = {x,result};

	return p;
}


