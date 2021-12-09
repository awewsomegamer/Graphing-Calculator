#include <iostream>
#include <windows.h>
#include "../include/Window.h"
#include "../include/Interpreter.h"
#include "../include/Graph/Graph.h"
#include <math.h>

using namespace std;

double it = 0;

//double rc = 0;
//double gc = 0;
//double bc = 0;

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
		glOrtho(wind.get_width(),wind.get_width(), wind.get_height(), wind.get_height(), 1, 1000000);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		wind.update();
//		i.run_line("draw_triangle()");
		g.update(wind.get_width(), wind.get_height());


		glRotated(it, 1, 1, 1);

//		g.plot_smooth_lines("y = math.pow(x,2)", GL_TRIANGLE_FAN);
//		g.plot_smooth_lines("y = -math.pow(x,2)", GL_TRIANGLE_STRIP);

		g.plot_smooth_lines("y = math.pow(x,2)", GL_TRIANGLE_STRIP);

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

		glRotated(-it, 1, 1, 1);
//		it++;

//		if (rc <= 1)
//			rc+=0.1;
//
//		if (rc >=1 && gc <= 1)
//			gc+=0.1;
//
//		if (gc >= 1 && bc <= 1)
//			bc+=0.1;
//
//		if (rc + gc + bc >= 3){
//			rc = 0;
//			gc = 0;
//			bc = 0;
//		}





		wind.render();

		glPopMatrix();
	}

	return 0;
}
