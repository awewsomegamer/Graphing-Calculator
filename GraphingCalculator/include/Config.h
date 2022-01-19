#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

class Config{
public:
	Config();
	void read(std::string);

	std::vector<std::vector<float>> themes;

	float background[3] = {0,0,0};
	float axis[3] = {1,1,1};
	float max_speed = 10;
	float min_speed = 0.01;
	float speed_increment = 0.01;
	float max_scale = 2;
	float min_scale = 0.01;
	float scale_speed = 0.01;
	float fineness = 0.1;
	float start_zoom = 0.1;

	int default_theme = 0;
	int move_camera_left = GLFW_KEY_LEFT;
	int move_camera_right = GLFW_KEY_RIGHT;
	int move_camera_up = GLFW_KEY_UP;
	int move_camera_down = GLFW_KEY_DOWN;
	int zoom_in = GLFW_KEY_E;
	int zoom_out = GLFW_KEY_Q;
	int increase_speed = GLFW_KEY_D;
	int decrease_speed = GLFW_KEY_A;
	int change_theme_up = GLFW_KEY_O;
	int change_theme_down = GLFW_KEY_I;

	bool show_grid = false;
	bool use_theme = true;
};

#endif
