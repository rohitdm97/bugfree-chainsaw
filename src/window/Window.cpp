#include "Window.h"
#include <debug.h>

void framebuffer_size_callback(GLFWwindow* ref, int width, int height)
{
	glViewport(0, 0, width, height);
	auto windowE = Window::instances.find(ref);
	if (windowE != Window::instances.end()) {
		auto window = windowE->second;
		window->lastX = width / 2;
		window->lastY = height / 2;
	}
}

void mouse_cursor_pos_callback(GLFWwindow* ref, double xpos, double ypos)
{
	auto windowE = Window::instances.find(ref);
	if (windowE != Window::instances.end()) {
		auto window = windowE->second;
		window->HandleMousePosition(xpos, ypos);
	}
}

void mouse_scroll_callback(GLFWwindow* ref, double xoffset, double yoffset)
{
	auto windowE = Window::instances.find(ref);
	if (windowE != Window::instances.end()) {
		auto window = windowE->second;
		window->HandleMouseScroll(xoffset, yoffset);
	}
}

void Window::RegisterCallbacks()
{
	glfwSetFramebufferSizeCallback(ref, framebuffer_size_callback);
	glfwSetCursorPosCallback(ref, mouse_cursor_pos_callback);
	glfwSetScrollCallback(ref, mouse_scroll_callback);
}


Window::Window(const int width, const int height, const char* title)
{
	Window::width = width;
	Window::height = height;
	ref = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ref == NULL) {
		glfwTerminate();
	}
	Window::lastX = width / 2;
	Window::lastY = height / 2;
	Window::firstMouse = true;

	Window::instances[ref] = this;
}

void Window::Activate()
{
	glfwMakeContextCurrent(ref);
}

void Window::Delete()
{
	glfwDestroyWindow(ref);
}

void Window::SetCamera(Camera& camera)
{
	Window::camera = &camera;
}

void Window::HandleMousePosition(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (camera) {
		camera->ProcessMouseMovement((float)xoffset, (float)yoffset);
	}
}

void Window::HandleMouseScroll(double xoffset, double yoffset)
{
	if (camera) {
		camera->ProcessMouseScroll((float)yoffset);
	}

}

void Window::HandleKeyboardInput(double delta)
{
	if (glfwGetKey(ref, GLFW_KEY_ESCAPE) == GLFW_PRESS && glfwGetKey(ref, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(ref, true);
	}
	if (glfwGetKey(ref, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		lastX = width / 2;
		lastY = height / 2;
		firstMouse = true;
	}

	if (camera)
	{
		if (glfwGetKey(ref, GLFW_KEY_W) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera::FORWARD, delta);
		if (glfwGetKey(ref, GLFW_KEY_S) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera::BACKWARD, delta);
		if (glfwGetKey(ref, GLFW_KEY_A) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera::LEFT, delta);
		if (glfwGetKey(ref, GLFW_KEY_D) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera::RIGHT, delta);
	}
}


