#include <iostream>
#include "../include/Window.h"

int main(){
	Window wind(500, 500, "Hello OpenGL");

	while (!wind.should_close()){
		wind.update();
		wind.render();
	}

	return 0;
}
