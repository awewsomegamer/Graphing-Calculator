#include "../include/Window.h"
#include "../include/Log.h"

// Window object
GLFWwindow* window;

// Array of keys
bool keys[GLFW_KEY_LAST];

// Original width and heigh
int cw = 500;
int ch = 500;

// Call backs
void window_size_callback(GLFWwindow* window, int w, int h){
	cw = w;
	ch = h;

	glViewport(0,0,w,h);
}

void keyboard_callback(GLFWwindow* window, int key, int scan, int action, int mods){
	keys[key] = (action != GLFW_RELEASE);
}

// Set callbacks into window so that they function
void make_callbacks(){
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, keyboard_callback);
}

// Initialize GLFW, create a window with size of cw and ch and center it
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

// Update the window with the config object being passed
void Window::update(Config c){
	glClearColor(c.background[0], c.background[1], c.background[2], 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
}

// Render the window
void Window::render(){
	glfwSwapBuffers(window);
}

// Set a key in the keys array
void Window::set_key(int key, bool value){
	keys[key] = value;
}

// Returns if the window should close
bool Window::should_close(){
	return glfwWindowShouldClose(window);
}

// Check the value of a key
bool Window::get_key(int key){
	return keys[key];
}

// Get the width of the window
int Window::get_width(){
	return cw;
}

// Get the height of the window
int Window::get_height(){
	return ch;
}
