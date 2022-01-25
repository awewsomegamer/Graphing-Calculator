#include "../../include/Graph/Graph.h"
#include "../../include/Log.h"
#include "../../include/Interpreter.h"
#include "../../include/Audio.h"
#include <math.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <pthread.h>
#include <string>

using namespace std;

// Functions vecto
std::vector<std::string> functions;

//Define mutex to be able to synchronize threads
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
// Checks if the point is within the range of the camera
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

// Add function to functions vector
void Graph::plot(std::string function){
	functions.push_back(function);
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

// Render the functions in functions vector
void Graph::render(){
//	pthread_t threads[functions.size()];
//
//	int i = 0;
	for (auto& v : functions){
		glBegin(GL_TRIANGLE_STRIP);
		std::vector<double> points;

		for (double x = -cx-total_x-scale; x <= -cx+total_x+scale; x+=fineness){
			Point point = get_point(v, x, x);

			if ((point.has_inequality && point.inequality_result) || !(point.has_inequality)){
				points.push_back(point.y);

				glColor3f(x,point.y, 0.5);

				if (v.find("x") != -1 && v.find("y") == -1)
					glVertex3d(x, (double)(point.y), 0);

				if (v.find("y") != -1 && v.find("x") == -1)
					glVertex3d((double)(point.y), x, 0);
			}
	}

	// This code is slow and needs to be optimized
	if (v.find("x") != -1 && v.find("y") != -1){
		for (double x = -cx-total_x-scale; x <= -cx+total_x+scale; x+=fineness){
			for (double y = -cy-total_x; y <= -cy+total_y; y+=fineness*2){
				Point point = get_point(v, x, y);

				if ((point.has_inequality && point.inequality_result) || !(point.has_inequality)){
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


// Get the total calculated total x
int Graph::get_total_x(){
	return total_x;
}

// Get the total calculated total y
int Graph::get_total_y(){
	return total_y;
}

// Use Lua to calculate the value of a function
Point Graph::get_point(std::string f, double x, double y){
	lua_pushnumber(i.get_state(), x);
	lua_setglobal(i.get_state(), "x");
	lua_pushnumber(i.get_state(), y);
	lua_setglobal(i.get_state(), "y");

	// Check for equal sign / inequality sign
	int sign = 0;
	int sign_loc = 10;

	std::string signs[] = {">","<",">=","<=","!=","="};

	int offset = f.find("=")+1;
	int color_property_offset = f.find("C:");

	for (sign = 0; sign < 6; sign++){
		if (f.substr(offset).find(signs[sign]) != -1){
			sign_loc = f.substr(offset).find(signs[sign])+offset;
			break;
		}
	}

	// Seperate equation from inequality, if sign is 6 there is no sign, and color
	std::string equation = sign == 6 ? f : f.substr(0, sign_loc);
	std::string inequality = "f = "+(sign == 6 ? "0" : f.substr(sign_loc+(sign != 6 ? signs[sign].size() : 0), (color_property_offset == -1 ? f.size() : color_property_offset)));
	std::string color = color_property_offset == -1 ? "" : "c = "+f.substr(color_property_offset);

	i.run_line(equation);

	lua_getglobal(i.get_state(), "f");

	double result = 0;

	if (lua_isnumber(i.get_state(), -1)){
		result = (double)lua_tonumber(i.get_state(), -1);
	}

	lua_pop(i.get_state(), -1);

	i.run_line(inequality);

	lua_getglobal(i.get_state(), "f");

	double inequality_d = 0;

	if (lua_isnumber(i.get_state(), -1)){
		inequality_d = (double)lua_tonumber(i.get_state(), -1);
	}

	lua_pop(i.get_state(), -1); // Pop result

	bool draw = true;

	switch (sign){
	case 0: // >
		if (result < inequality_d)
			draw = false;

		break;

	case 1: // <
		if (result > inequality_d)
			draw = false;

		break;

	case 2: // >=
		if (result <= inequality_d)
			draw = false;

		break;

	case 3: // <=
		if (result >= inequality_d)
			draw = false;

		break;

	case 4: // !=
		if (result == inequality_d)
			draw = false;

		break;

	case 5: // =
		if (result != inequality_d)
			draw = false;

		break;
	}

	lua_pop(i.get_state(), -1); // Pop inequality_d

	lua_pop(i.get_state(), -1); // Pop Y
	lua_pop(i.get_state(), -1); // Pop X

	Point p = {x,result};

	p.has_inequality = !(sign_loc == 6);
	p.inequality_result = draw;

	if (color_property_offset != -1){
		i.run_line(color);

		lua_getglobal(i.get_state(), "c");

		double colors[3];

		lua_pushnil(i.get_state());

		int itt = 0;

		while (lua_next(i.get_state(), -2)){
			if (lua_isnumber(i.get_state(), -1)){
				colors[itt++] = (float)(lua_tonumber(i.get_state(), -1));
			}

			lua_pop(i.get_state(), 1);
		}

		lua_pop(i.get_state(), 1); // Pop colors array

		p.r = colors[0];
		p.g = colors[1];
		p.b = colors[2];
		p.custom_color = true;
	}

	return p;
}

// Setter for functions vector
void Graph::set_graphs(std::vector<std::string> graphs){
	functions = graphs;
}

