#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "../Config.h"

class Graph{
public:
	struct Point{
		double x;
		double y;
		double r;
		double g;
		double b;
	};

	Graph(Config conf);

	void update(int w, int h, double fineness, double gx, double gy);
	void plot(std::string function, int mode);

	int get_total_x();
	int get_total_y();
	bool check_render(Point p, int minimizer);

	Point get_point(std::string f, double x, double y);
};

#endif
