#include "../../include/Graph/Graph.h"
#include "../../include/Log.h"
#include "../../include/Interpreter.h"
#include "../../include/Audio.h"
#include <math.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <sstream>

using namespace std;

// Function mode
map<string, int> functions;

//Define mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variables to be updated
double fineness = 0;
double scale = 0.1;
double cx = 0;
double cy = 0;

Interpreter i(true);
Audio audio;

int total_x = 10;
int total_y = 10;

// Initialize
Graph::Graph(Config conf){
	fineness = conf.fineness;
}

// Update variables from the main function
void Graph::update(int w, int h, double s, double gx, double gy){
	total_x = w/100; // Figure out window width in OpenGL numbers (500 = 5)
	total_y = h/100; // Figure out window height in OpenGL numbers (500 = 5)
	scale = s; // Set global variables from maind
	cx = gx;
	cy = gy;
}


//Add comfort features like x^2 = math.pow(x,2) or don't
//std::string comfortize(std::string string){
//
//
//	return "";
//}

// This function is not used
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

// Add function and it's mode to the map
void Graph::plot(std::string function, int mode){
	functions.emplace(function, mode);
}

// Calculate graphs
//void* calculate_graph(void* arg){
//	pthread_mutex_lock(&mutex);
//
//
//	std::string v = *((std::string*)arg);
//
//	std::cout << "From <draw_graph> :: " << v << std::endl;
//
//	// Calculate all points and return them to main thread to draw
//
//	pthread_mutex_unlock(&mutex);
//
//	pthread_exit(0);
//}

// Render the graphs
void Graph::render(){
	pthread_t threads[functions.size()];

	int i = 0;
	for (auto& v : functions){
		glBegin(GL_TRIANGLE_STRIP);
		std::vector<double> points;

		for (double x = -cx-total_x-scale; x <= -cx+total_x+scale; x+=fineness){
			// Check for equal sign / inequality sign
			int sign = 0;
			int sign_loc = 10;

			std::string signs[] = {">","<",">=","<=","!=","="};
			std::string removef = v.first;

			int offset = removef.find("=")+1;
			removef = removef.substr(offset);

			for (sign = 0; sign < 6; sign++){
				if (removef.find(signs[sign]) != -1){
					sign_loc = removef.find(signs[sign])+offset;
					break;
				}
			}

			// Seperate equation from inequality, if sign is 6 there is no sign
			std::string equation = sign == 6 ? v.first : v.first.substr(0, sign_loc);
			std::string inequality = "f = "+(sign == 6 ? "0" : v.first.substr(sign_loc+(sign != 6 ? signs[sign].size() : 0)));

			Point point = get_point(equation, x, x);
			Point ineq = sign != 6 ? get_point(inequality, x, x) : get_point("", 0, 0);
			bool draw = true;

			switch (sign){
			case 0: // >
				if (point.y < ineq.y)
					draw = false;

				break;

			case 1: // <
				if (point.y > ineq.y)
					draw = false;

				break;

			case 2: // >=
				if (point.y <= ineq.y)
					draw = false;

				break;

			case 3: // <=
				if (point.y >= ineq.y)
					draw = false;

				break;

			case 4: // !=
				if (point.y == ineq.y)
					draw = false;

				break;

			case 5: // =
				if (point.y != ineq.y)
					draw = false;

				break;
			}

			if (draw){
				points.push_back(point.y);

				glColor3f(x,point.y, 0.5);

				if (v.first.find("x") != -1 && v.first.find("y") == -1)
					glVertex3d(x, (double)(point.y), 0);

				if (v.first.find("y") != -1 && v.first.find("x") == -1)
					glVertex3d((double)(point.y), x, 0);
			}
	}

	// This code is slow and needs to be optimized
	if (v.first.find("x") != -1 && v.first.find("y") != -1){
		for (double x = -cx-total_x-scale; x <= -cx+total_x+scale; x+=fineness){
			for (double y = -cy-total_x; y <= -cy+total_y; y+=fineness*2){
				// Check for equal sign / inequality sign
				int sign = 0;
				int sign_loc = 10;

				std::string signs[] = {">","<",">=","<=","!=","="};
				std::string removef = v.first;

				int offset = removef.find("=")+1;
				removef = removef.substr(offset);

				for (sign = 0; sign < 6; sign++){
					if (removef.find(signs[sign]) != -1){
						sign_loc = removef.find(signs[sign])+offset;
						break;
					}
				}

				// Seperate equation from inequality, if sign is 6 there is no sign
				std::string equation = sign == 6 ? v.first : v.first.substr(0, sign_loc);
				std::string inequality = "f = "+(sign == 6 ? "0" : v.first.substr(sign_loc+(sign != 6 ? signs[sign].size() : 0)));

				Point point = get_point(equation, x, y);
				Point ineq = sign != 6 ? get_point(inequality, x, y) : get_point("", 0, 0);
				bool draw = true;

				switch (sign){
				case 0: // >
					if (point.y < ineq.y)
						draw = false;

					break;

				case 1: // <
					if (point.y > ineq.y)
						draw = false;

					break;

				case 2: // >=
					if (point.y <= ineq.y)
						draw = false;

					break;

				case 3: // <=
					if (point.y >= ineq.y)
						draw = false;

					break;

				case 4: // !=
					if (point.y == ineq.y)
						draw = false;

					break;

				case 5: // =
					if (point.y != ineq.y)
						draw = false;

					break;
				}

				if (draw){
					points.push_back(point.y);

					glColor3f(x,point.y, 0.5);

					glVertex3d(x, (double)(point.y), 0);
				}
			}
		}
	}

	// Play sound
	audio.play(audio.find_pitch(points));

	glEnd();

	}

//		std::cout << "From caller :: " << v.first << std::endl;
//
//		pthread_create(&threads[i], 0, draw_graph, (void*)&v.first);
//
//		i++;

//	for (i = 0; i < functions.size(); i++){
//		pthread_join(threads[i], 0);
//	}
}
//	std::cout << scale << std::endl;
//		for (double x = -total_x+1; x < total_x; x+=fineness){
//			if (check_render(point, 1)){
//			}
//	}

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


// Get the total calculated total x
int Graph::get_total_x(){
	return total_x;
}

// Get the total calculated total y
int Graph::get_total_y(){
	return total_y;
}

// Use Lua to calculate the value of a function
Graph::Point get_point(std::string f, double x, double y){
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
	lua_pop(i.get_state(), -1);

// f = math.pow(x,3) > 0
// c = [r,g,b]
// This code is to set the color of the graph
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


