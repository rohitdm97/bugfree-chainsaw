#pragma once
#ifndef __WINDOW_CLASS_H
#define __WINDOW_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Window
{
public:
	GLFWwindow* ref;
	int width;
	int height;
	Window(const int width, const int height, const char* title);

	void Activate();
	void Delete();
};

#endif // !__WINDOW_CLASS_H
