#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class Graph{
public:
	struct Point{
		int x;
		int y;
	};

	Graph();

	void update(int w, int h);

	Point get_point(std::string f, int x);
};

#endif
