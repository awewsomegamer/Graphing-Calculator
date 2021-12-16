#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>

class Config{
public:
	Config();
	void read(std::string);

	float background[3];
	float axis[3];
	float max_speed = 10;
	float min_speed = 0.01;
	float speed_increment = 0.01;
	float max_scale = 2;
	float min_scale = 0.01;
	float scale_speed = 0.01;
	float fineness = 0.1;
	bool show_grid = false;

//	int n_themes = 256;
//	int themes[n_themes][10]; // bg, fg, graph color
};

#endif
