#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "../Config.h"

// Point structure
struct Point{
	double x;
	double y;
	int r;
	int g;
	int b;
	bool custom_color = false;
	bool has_inequality = false;
	bool inequality_result;
};

//void* draw_graph(void*);

class Graph{
public:
	Graph(Config conf);

	void update(int w, int h, double fineness, double gx, double gy);
	void plot(std::string function);
	void render();
	void set_graphs(std::vector<std::string> graphs);

	int get_total_x();
	int get_total_y();
	bool check_render(Point p, int minimizer);

	Point get_point(std::string f, double x, double y);
};

#endif
