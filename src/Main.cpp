#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include <window/Window.h>
#include <render/Shader.h>
#include <model/Mesh.h>
#include <texture/Texture.h>

const bool wireframe = false;
const int width = 1024;
const int height = 768;

//extern std::vector<glm::vec3> triangleVertices1;
//extern std::vector<unsigned int> triangleIndices1;


extern std::vector<Vertex> vertices;
extern std::vector<unsigned int> indices;

std::map<GLFWwindow*, Window*> Window::instances;

void printMachineInfo() {
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: [" << nrAttributes << "]" << std::endl;
}

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window(width, height, "This is the title");
	if (window.ref == NULL) {
		return -1;
	}
	window.Activate();
	window.RegisterCallbacks();

	gladLoadGL();
	printMachineInfo();

	glViewport(0, 0, window.width, window.height);
	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	};

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Mesh mesh(vertices, indices);
	Texture texture("wall.jpg");
	Camera camera(glm::vec3(0, 0, 3), window.width, window.height);
	window.SetCamera(camera);

	double delta = 0;
	double lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(window.ref)) {
		double currentFrame = glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.HandleKeyboardInput(delta);

		glClearColor(0.07f, 0.85f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		texture.Bind();
		mesh.Render(camera);


		glfwSwapBuffers(window.ref);
		glfwPollEvents();
	}

	// mesh.Delete();
	window.Delete();
	glfwTerminate();
	return 0;
}

