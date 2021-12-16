#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "config.h"

class Window{
public:
	Window(int w, int h, std::string title);

	void update(Config c);
	void render();

	bool should_close();
	bool get_key(int key);
	int get_width();
	int get_height();

};

#endif
