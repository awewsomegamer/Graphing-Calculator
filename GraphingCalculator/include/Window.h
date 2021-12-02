#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class Window{
public:
	Window(int w, int h, std::string title);

	void update();
	void render();

	bool should_close();
private:
	GLFWwindow* window;
};

#endif
