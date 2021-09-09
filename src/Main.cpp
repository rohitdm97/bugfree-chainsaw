#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<window/Window.h>

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window(800, 800, "This is the title");
	if (window.ref == NULL) {
		return -1;
	}
	window.Activate();

	gladLoadGL();

	glViewport(0, 0, window.width, window.height);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window.ref);

	while (!glfwWindowShouldClose(window.ref)) {
		glfwPollEvents();
	}

	window.Delete();
	glfwTerminate();
	return 0;
}

