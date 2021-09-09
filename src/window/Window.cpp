#include "Window.h"

Window::Window(const int width, const int height, const char* title)
{
	Window::width = width;
	Window::height = height;
	ref = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ref == NULL) {
		glfwTerminate();
	}
}

void Window::Activate()
{
	glfwMakeContextCurrent(ref);
}

void Window::Delete()
{
	glfwDestroyWindow(ref);
}
