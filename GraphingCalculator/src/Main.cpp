#include <iostream>
#include "../include/Window.h"
#include "../include/Audio.h"
#include "../include/Interpreter.h"
#include "../include/Config.h"
#include "../include/Graph/Graph.h"
#include <math.h>
#include <fstream>

using namespace std;

double s  = 0.1; // Scale
double s_inv  = 1; // Inverted scale
double gx = 0; // Camera X (could be thought of as graph x)
double gy = 0; // Camera Y (could be thought of as graph y)
double speed = 0.01; // Camera speed
int theme_index = 0; // Current theme index

// Set the graphs to render
void load_graphs(Graph *g){
	ifstream graphs_f("graphs.lua");
	std::vector<std::string> graphs_v = std::vector<std::string>();

	std::string line;
	while (getline(graphs_f, line))
		graphs_v.push_back(line);

	g->set_graphs(graphs_v);
}

int main(){
	Config conf;
	conf.read("config.lua");

	// Start variables
	theme_index = conf.default_theme;
	s = conf.start_zoom;
	s_inv = conf.start_zoom*10;

	Window wind(500, 500, "CPlusPlotter");
	Interpreter i(true);
	Graph g(conf);

	load_graphs(&g);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Switch to line mode to make it so that GL_TRIANGLE_STRIP (connected line) and GL_TRIANGLE_FAN (filled) create nicer graphs
	glCullFace(GL_FRONT_AND_BACK); // Cull some faces

	while (!wind.should_close()){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glPushMatrix();

		wind.update(conf);
		g.update(wind.get_width()*10, wind.get_height()*10, s_inv, gx, gy); // Update the grapher with some variables

		// Apply transformations
		glScaled(s,s,0);
		glTranslated(gx, gy, 0);

		// TODO: OPTOMIZE G.PLOT(F, M);
//		g.plot("f = math.pow(x,3) > 0", GL_TRIANGLE_STRIP);
//		g.plot("f = math.pow(y,2) = 3", GL_TRIANGLE_STRIP);
//		g.plot("f = math.sin(y) < 0.5");
//		g.plot("f = math.abs(math.sin(x)*3) != 0", 0);
//		g.plot("if (x < 2) then f = x else f = 1 end", 0);
//		g.plot("y = math.pow(x+5,3)+1", GL_TRIANGLE_STRIP);
//		g.plot("y = math.pow(x-1,"+to_string(e)+") c = {1,1,1}", GL_TRIANGLE_STRIP);
//		g.plot("y = math.max(-math.pow(x,2)+2,1)",GL_TRIANGLE_FAN);
//		g.plot("f = math.cos(x)", GL_TRIANGLE_STRIP);
//		g.plot("f = -math.sin(math.sin(x)) + math.cos(math.sin(x, y)) + math.cos(x) ", GL_TRIANGLE_STRIP);
//		g.plot("y = factorial(x)", GL_TRIANGLE_STRIP);//\n y = math.sin(y)
//		g.plot("y = math.sin(math.cos(math.tan(x)))", GL_TRIANGLE_STRIP); ///-math.sin(math.cos(math.tan(x,y))) +  + math.sin(math.cos(math.tan(y)))
//		g.plot("f = math.sqrt(x)", GL_TRIANGLE_STRIP);

		// Render graphs
		g.render();

		// Render the grid (if conf.show_grid is true)
		if (conf.show_grid){
			for (double y = -10; y < 10; y+=0.1){
				for (double x = -10; x < 10; x+=0.1){
					glBegin(GL_LINES);
						//glColor3f(x,0,y);
						glColor3f(0.5,0.5,0.5);
						glVertex3f(x,10,0);

						//glColor3f(y,0,x);
						glColor3f(0.5,0.5,0.5);
						glVertex3f(x,-10,0);
					glEnd();

					glBegin(GL_LINES);
						//glColor3f(x,y,0);
						glColor3f(0.5,0.5,0.5);
						glVertex3f(10,y,0);

						//glColor3f(y,x,0);
						glColor3f(0.5,0.5,0.5);
						glVertex3f(-10,y,0);
					glEnd();
				}
			}
		}

		// Lines of the cartesian plane
		glBegin(GL_LINES);
			glColor3f(conf.axis[0],conf.axis[1],conf.axis[2]);
			glVertex3f(0,1000000000,0);

			glColor3f(conf.axis[0],conf.axis[1],conf.axis[2]);
			glVertex3f(0,-1000000000,0);
		glEnd();

		glBegin(GL_LINES);
			glColor3f(conf.axis[0],conf.axis[1],conf.axis[2]);
			glVertex3f(1000000000,0,0);

			glColor3f(conf.axis[0],conf.axis[1],conf.axis[2]);
			glVertex3f(-1000000000,0,0);
		glEnd();

		glTranslated(-gx, -gy, 0);
		glScaled(-s,-s,0);

		// User input checks (conf.<variable_name> should explain what each one stands for)
		if (s > conf.min_scale+conf.min_scale && wind.get_key(conf.zoom_out))
			s-=conf.scale_speed;
		if (s < conf.max_scale && wind.get_key(conf.zoom_in))
			s+=conf.scale_speed;

		if (s_inv > conf.min_scale && wind.get_key(conf.zoom_in))
			s_inv-=conf.scale_speed*4;
		if (s_inv < conf.max_scale && wind.get_key(conf.zoom_out))
			s_inv+=conf.scale_speed*4;

		if (wind.get_key(conf.move_camera_up))
			gy-=speed;
		if (wind.get_key(conf.move_camera_down))
			gy+=speed;

		if (wind.get_key(conf.move_camera_right))
			gx-=speed;
		if (wind.get_key(conf.move_camera_left))
			gx+=speed;

		if (speed > conf.min_speed && wind.get_key(conf.decrease_speed))
			speed-=conf.speed_increment;
		if (speed < conf.max_speed && wind.get_key(conf.increase_speed))
			speed+=conf.speed_increment;

		if (wind.get_key(conf.reload_graphs))
			load_graphs(&g);

		if (theme_index > 0 && wind.get_key(conf.change_theme_down)){
			theme_index--;
			wind.set_key(conf.change_theme_down, false);
		}

		if (theme_index < (int)conf.themes.size()-1 && wind.get_key(conf.change_theme_up)){
			theme_index++;
			wind.set_key(conf.change_theme_up, false);
		}

		if (conf.use_theme){
			for (int i = 0; i < 3; i++){
				conf.background[i] = conf.themes[theme_index][i];
				conf.axis[i] = conf.themes[theme_index][i+3];
			}
		}

		wind.render();

		glPopMatrix();
	}

	return 0;
}
