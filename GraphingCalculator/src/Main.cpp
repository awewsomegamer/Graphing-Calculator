#include <iostream>
#include <windows.h>
#include "../include/Window.h"
#include "../include/Interpreter.h"
#include "../include/Graph/Graph.h"
#include <math.h>

using namespace std;

double it = 0;
double e = 1;
double s  = 1;


int main(){
	Window wind(500, 500, "Hello OpenGL");
	Interpreter i;
	Graph g;

	Graph::Point p = g.get_point("y = 2*math.pow(x,2)", 4); // same as 2x^2 (x = 4)

	cout << "X :: " << p.x << " Y :: " << p.y << endl;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!wind.should_close()){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-100,-100,-100,-100, 1, 1000000);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		wind.update();
//		i.run_line("draw_triangle()");
		g.update(wind.get_width(), wind.get_height());


		glRotated(sin(it), 1, 0, 1);
		glScaled(s,s,0);
//		g.plot_smooth_lines("y = math.pow(x,2)", GL_TRIANGLE_FAN);
//		g.plot_smooth_lines("y = -math.pow(x,2)", GL_TRIANGLE_STRIP);
//
//		g.plot_smooth_lines("y = math.pow(x,3)", GL_TRIANGLE_STRIP);
		g.plot_smooth_lines("y = math.pow(x+"+to_string(0)+","+to_string(e)+")", GL_TRIANGLE_STRIP);

//		for (double y = -1; y < 1; y+=0.1){
//			for (double x = -1; x < 1; x+=0.1){
//				glBegin(GL_LINES);
//					glColor3f(x,0,y);
//					glVertex3f(x,1,0);
//
//					glColor3f(y,0,x);
//					glVertex3f(x,-1,0);
//				glEnd();
//
//				glBegin(GL_LINES);
//					glColor3f(x,y,0);
//					glVertex3f(1,y,0);
//
//					glColor3f(y,x,0);
//					glVertex3f(-1,y,0);
//				glEnd();
//			}
//		}
//
		glBegin(GL_LINES);
			glColor3f(1,1,1);
			glVertex3f(0,1,0);

			glColor3f(1,1,1);
			glVertex3f(0,-1,0);
		glEnd();

		glBegin(GL_LINES);
			glColor3f(1,1,1);
			glVertex3f(1,0,0);

			glColor3f(1,1,1);
			glVertex3f(-1,0,0);
		glEnd();

		glScaled(-s,-s,0);
		glRotated(-sin(it), 1, 0, 1);
		it+=0.1;
		e+=0.01;
		if (s > 0.001)
			s-=0.001;

		cout << s << endl;

		wind.render();

		glPopMatrix();
	}

	return 0;
}
