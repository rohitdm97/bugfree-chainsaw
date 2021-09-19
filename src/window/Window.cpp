#include "Window.h"
#include <debug.h>

#include "texture/Texture.h"

void should_close_callback(GLFWwindow* ref)
{
	auto windowE = Window::instances.find(ref);
	if (windowE != Window::instances.end()) {
		auto window = windowE->second;
		window->ShouldClose = true;
	}
}

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

void mouse_button_callback(GLFWwindow* ref, int button, int action, int mods)
{
	auto windowE = Window::instances.find(ref);
	if (windowE != Window::instances.end()) {
		auto window = windowE->second;
		window->HandleMouseButtonClicked(button, action, mods);
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
	glfwSetWindowCloseCallback(ref, should_close_callback);
	glfwSetFramebufferSizeCallback(ref, framebuffer_size_callback);
	glfwSetMouseButtonCallback(ref, mouse_button_callback);
	glfwSetCursorPosCallback(ref, mouse_cursor_pos_callback);
	glfwSetScrollCallback(ref, mouse_scroll_callback);
}

void printMachineInfo() {
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: [" << nrAttributes << "]" << std::endl;
}

Window::Window(const int width, const int height, const char* title)
{
	Window::width = width;
	Window::height = height;
	Window::lastX = width / 2;
	Window::lastY = height / 2;
	Window::mouseClicked = false;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	ref = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ref == NULL) {
		glfwTerminate();
	}
	else
	{
		// only add window if it is working
		Window::instances[ref] = this;
	}
}

void Window::SetWireframe(bool active)
{
	Window::wireframe = active;
}

void Window::Activate()
{
	glfwMakeContextCurrent(ref);
	RegisterCallbacks();

	gladLoadGL();
	printMachineInfo();

	glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
	glViewport(0, 0, width, height);

	Texture::Init();

	glEnable(GL_DEPTH_TEST);
}

void Window::Delete()
{
	glfwDestroyWindow(ref);
}

void Window::SetCamera(std::shared_ptr<Camera> camera)
{
	Window::camera = camera;
}

void Window::HandleMousePosition(double xpos, double ypos)
{
	if (mouseClicked)
	{
		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		if (auto c = camera.lock()) {
			c->ProcessMouseMovement((float)xoffset, (float)yoffset);
		}
	}
}

void Window::HandleMouseScroll(double xoffset, double yoffset)
{
	if (auto c = camera.lock()) {
		c->ProcessMouseScroll((float)yoffset);
	}

}

void Window::HandleKeyboardInput(double delta)
{
	if (glfwGetKey(ref, GLFW_KEY_ESCAPE) == GLFW_PRESS && glfwGetKey(ref, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(ref, true);
	}

	if (auto c = camera.lock())
	{
		if (glfwGetKey(ref, GLFW_KEY_W) == GLFW_PRESS)
			c->ProcessKeyboard(Camera::FORWARD, delta);
		if (glfwGetKey(ref, GLFW_KEY_S) == GLFW_PRESS)
			c->ProcessKeyboard(Camera::BACKWARD, delta);
		if (glfwGetKey(ref, GLFW_KEY_A) == GLFW_PRESS)
			c->ProcessKeyboard(Camera::LEFT, delta);
		if (glfwGetKey(ref, GLFW_KEY_D) == GLFW_PRESS)
			c->ProcessKeyboard(Camera::RIGHT, delta);
	}
}

void Window::HandleMouseButtonClicked(int button, int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_1)
	{
		return;
	}
	if (action == GLFW_PRESS)
	{
		glfwGetCursorPos(ref, &lastX, &lastY);
		mouseClicked = !mouseClicked;
	}
}


