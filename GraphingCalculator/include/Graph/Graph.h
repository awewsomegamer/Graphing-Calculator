#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class Graph{
public:
	struct Point{
		double x;
		double y;
		double r;
		double g;
		double b;
	};

	Graph();

	void update(int w, int h);
	void plot(std::string function, int mode);

	int get_total_x();
	int get_total_y();

	Point get_point(std::string f, double x, double y);
};

#endif
