#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class Graph{
public:
	struct Point{
		double x;
		double y;
	};

	Graph();

	void update(int w, int h);
	void plot_smooth_lines(std::string function, int mode);
	void plot_rough_lines(std::string function);

	int get_total_x();
	int get_total_y();

	Point get_point(std::string f, double x);
};

#endif
