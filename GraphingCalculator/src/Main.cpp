#include <iostream>
#include "../include/Window.h"
#include "../include/Interpreter.h"
#include "../include/Graph/Graph.h"

using namespace std;

int main(){
	Window wind(500, 500, "Hello OpenGL");
	Interpreter i;
	Graph g;

	Graph::Point p = g.get_point("y = 2*math.pow(x,2)", 4); // same as 2x^2 (x = 4)

	cout << "X :: " << p.x << " Y :: " << p.y << endl;


	while (!wind.should_close()){
		glOrtho(wind.get_width(),-wind.get_width(), -wind.get_height(), wind.get_height(), 0, 100);

		wind.update();
		i.run_line("draw_triangle()");
		g.update(wind.get_width(), wind.get_height());

		wind.render();
	}

	return 0;
}
