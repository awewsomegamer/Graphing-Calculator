#include <iostream>
#include <windows.h>
#include "../include/Window.h"
#include "../include/Audio.h"
#include "../include/Interpreter.h"
#include "../include/Graph/Graph.h"
#include <math.h>

using namespace std;

double it = 0;
double e = 1;
double s  = 1;
double gx = 0;
double gy = 0;
double speed = 0.01;

int main(){
	Window wind(500, 500, "Hello OpenGL");
	Interpreter i;
	Graph g;
	Audio a;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!wind.should_close()){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-100,-100,-100,-100, 1, 1000000);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		wind.update();
		g.update(wind.get_width()*10, wind.get_height()*10);

		glScaled(s,s,0);
		glTranslated(gx, gy, 0);

//		g.plot("y = math.pow(x,3)", GL_TRIANGLE_FAN);
		g.plot("y = -math.pow(x,2)-10", GL_TRIANGLE_STRIP);

		g.plot("y = math.pow(x+5,3)+1", GL_TRIANGLE_STRIP);
		g.plot("y = math.pow(x-1,"+to_string(e)+") c = {1,1,1}", GL_TRIANGLE_STRIP);

//		for (double y = -10; y < 10; y+=0.1){
//			for (double x = -10; x < 10; x+=0.1){
//				glBegin(GL_LINES);
//					//glColor3f(x,0,y);
//					glColor3f(0.5,0.5,0.5);
//					glVertex3f(x,10,0);
//
//					//glColor3f(y,0,x);
//					glColor3f(0.5,0.5,0.5);
//					glVertex3f(x,-10,0);
//				glEnd();
//
//				glBegin(GL_LINES);
//					//glColor3f(x,y,0);
//					glColor3f(0.5,0.5,0.5);
//					glVertex3f(10,y,0);
//
//					//glColor3f(y,x,0);
//					glColor3f(0.5,0.5,0.5);
//					glVertex3f(-10,y,0);
//				glEnd();
//			}
//		}

		glBegin(GL_LINES);
			glColor3f(1,1,1);
			glVertex3f(0,1000000000,0);

			glColor3f(1,1,1);
			glVertex3f(0,-1000000000,0);
		glEnd();

		glBegin(GL_LINES);
			glColor3f(1,1,1);
			glVertex3f(1000000000,0,0);

			glColor3f(1,1,1);
			glVertex3f(-1000000000,0,0);
		glEnd();

		glTranslated(-gx, -gy, 0);
		glScaled(-s,-s,0);

		if (s > 0.01 && wind.get_key(GLFW_KEY_Q))
			s-=0.01;
		if (s < 2 && wind.get_key(GLFW_KEY_E))
			s+=0.01;

		if (wind.get_key(GLFW_KEY_UP))
			gy-=speed;
		if (wind.get_key(GLFW_KEY_DOWN))
			gy+=speed;

		if (wind.get_key(GLFW_KEY_RIGHT))
			gx-=speed;
		if (wind.get_key(GLFW_KEY_LEFT))
			gx+=speed;

		if (speed > 0.01 && wind.get_key(GLFW_KEY_A))
			speed-=0.01;
		if (speed < 2 && wind.get_key(GLFW_KEY_D))
			speed+=0.01;

		wind.render();

		glPopMatrix();
	}

	return 0;
}
