#include "../include/Window.h"
#include "../include/Log.h"

Window::Window(int w, int h, std::string title){
	if (!glfwInit()){
		LOG::log("Failed to initialize GLFW", LOG::FATAL);
		exit(1);
	}

	window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

	if (window == 0){
		LOG::log("Failed to create window", LOG::FATAL);
		exit(1);
	}

	const GLFWvidmode* vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int sw = vid_mode->width;
	int sh = vid_mode->height;

	glfwSetWindowPos(window, (sw-w)/2, (sh-h)/2);
	glfwMakeContextCurrent(window);

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
