#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "../Config.h"

//void* draw_graph(void*);

class Graph{
public:
	Graph(Config conf);

	// Point structure
	struct Point{
		double x;
		double y;
		double r;
		double g;
		double b;
	};

	Point get_point(std::string f, double x, double y);

	void update(int w, int h, double fineness, double gx, double gy);
	void plot(std::string function, int mode);
	void render();

	int get_total_x();
	int get_total_y();
	bool check_render(Point p, int minimizer);
};

#endif
