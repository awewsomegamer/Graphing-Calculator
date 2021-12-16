#include "../include/Window.h"
#include "../include/Log.h"

GLFWwindow* window;

bool keys[GLFW_KEY_LAST];

int cw = 500;
int ch = 500;

void window_size_callback(GLFWwindow* window, int w, int h){
	cw = w;
	ch = h;

	glViewport(0,0,w,h);
}

void keyboard_callback(GLFWwindow* window, int key, int scan, int action, int mods){
	keys[key] = (action != GLFW_RELEASE);
}

void make_callbacks(){
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, keyboard_callback);
}

Window::Window(int w, int h, std::string title){
	cw = w;
	ch = h;

	if (!glfwInit()){
		log("Failed to initialize GLFW", LFATAL);
		exit(1);
	}

	window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

	if (window == 0){
		log("Failed to create window", LFATAL);
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

void Window::update(Config c){
	glClearColor(c.background[0], c.background[1], c.background[2], 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
}

void Window::render(){
	glfwSwapBuffers(window);
}

void Window::set_key(int key, bool value){
	keys[key] = value;
}

bool Window::should_close(){
	return glfwWindowShouldClose(window);
}

bool Window::get_key(int key){
	return keys[key];
}

int Window::get_width(){
	return cw;
}

int Window::get_height(){
	return ch;
}
