#pragma once
#ifndef __WINDOW_CLASS_H
#define __WINDOW_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <memory>
#include <map>

#include"camera/Camera.h"

class Window
{
public:
	static std::map<GLFWwindow*, Window*> instances;
public:
	GLFWwindow* ref;
	bool mouseClicked = false;
	int width, height;
	double lastX, lastY;
	Camera* camera;
	bool wireframe = false;

	Window(const int width, const int height, const char* title);

	void SetWireframe(bool active);
	void Activate();
	void SetCamera(Camera& camera);
	void Delete();

	void HandleMousePosition(double xpos, double ypos);
	void HandleMouseScroll(double xoffset, double yoffset);
	void HandleKeyboardInput(double delta);
	void HandleMouseButtonClicked(int button, int action, int mods);
private:
	void RegisterCallbacks();
};

#endif // !__WINDOW_CLASS_H
