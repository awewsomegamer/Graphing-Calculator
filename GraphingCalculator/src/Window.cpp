#include "../include/Window.h"
#include "../include/Log.h"

GLFWwindow* window;

int cw = 500;
int ch = 500;

void window_size_callback(GLFWwindow* window, int w, int h){
	cw = w;
	ch = h;

	glViewport(0,0,w,h);
}

void make_callbacks(){
	glfwSetWindowSizeCallback(window, window_size_callback);
}

Window::Window(int w, int h, std::string title){
	cw = w;
	ch = h;

	if (!glfwInit()){
		log("Failed to initialize GLFW", FATAL);
		exit(1);
	}

	window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

	if (window == 0){
		log("Failed to create window", FATAL);
		exit(1);
	}

	const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int sw = vid_mode->width;
	int sh = vid_mode->height;

	glfwSetWindowPos(window, (sw-w)/2, (sh-h)/2);
	glfwMakeContextCurrent(window);
	make_callbacks();

	glfwSwapInterval(1);

	glfwShowWindow(window);

}

void Window::update(){
	glClearColor(0.1, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
}

void Window::render(){
	glfwSwapBuffers(window);
}

bool Window::should_close(){
	return glfwWindowShouldClose(window);
}

int Window::get_width(){
	return cw;
}

int Window::get_height(){
	return ch;
}
