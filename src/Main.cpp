#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

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

extern std::vector<Vertex> boxVertices;
extern std::vector<unsigned int> boxIndices;

std::map<GLFWwindow*, Window*> Window::instances;

glm::vec3 origin = glm::vec3(0, 0, 0);
glm::vec3 x_axis = glm::vec3(1, 0, 0);
glm::vec3 y_axis = glm::vec3(0, 1, 0);
glm::vec3 z_axis = glm::vec3(0, 0, 1);

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

	glEnable(GL_DEPTH_TEST);

	Shader shader("single_light");
	Mesh mesh(vertices, indices, std::make_unique<Shader>(shader));
	mesh.Move(glm::vec3(0.1, -0.2, 0));
	Texture texture("wall.jpg");
	Camera camera(glm::vec3(5, 5, 5), window.width, window.height, -135, -35);
	// camera.LookAt(glm::vec3(0, 0, 0));
	window.SetCamera(camera);

	Mesh lightBox(boxVertices, boxIndices, std::make_unique<Shader>("light"));
	lightBox.Move(glm::vec3(
		glm::rotate(glm::mat4(1), glm::radians(45.0f), y_axis)
		*
		glm::vec4(0, 0, 2, 1)
	));
	lightBox.Scale(0.05f);

	glm::vec3 light_color = glm::vec3(154, 227, 130);
	light_color /= 255.0;
	glm::vec3 rotation_axis = glm::normalize(glm::vec3(0, 1, 0));
	glm::vec4 light_position = glm::vec4(lightBox.position, 1);
	shader.Activate();
	shader.SetVec3("light_color", glm::vec3(1, 1, 1));
	shader.SetVec3("light_position", glm::vec3(light_position));

	double delta = 0;
	double lastFrame = glfwGetTime();

	double aggr = 0;
	int frameCtr = 0;
	// FPS
	double frames = 0;
	while (!glfwWindowShouldClose(window.ref)) {
		double currentFrame = glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;
		aggr += delta;

		window.HandleKeyboardInput(delta);

		glClearColor(0.17f, 0.45f, 0.87f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.Bind();

		double pi = 3.14159265;
		// theta = pi/8 * (2 + sin(2 pi f t))
		// d(theta) = pi/8 * (2 pi f cos(2 pi f t)) d(t)
		// f = 1/4
		// double theta = (pi / 8) * (2 * pi * (1.0/ 4) * cos(2 * pi * (1.0 / 4) * currentFrame) * delta);
		double f = 1.0 / 4;
		double span = pi / 4;
		double d_theta = delta * span / 2.0 * (2 * pi * f * cos(2 * pi * f * currentFrame));
		glm::mat4 rot = glm::rotate(glm::mat4(1), (float)d_theta, rotation_axis);
		light_position = rot * light_position;

		shader.Activate();
		shader.SetVec3("light_position", glm::vec3(light_position));
		shader.SetVec3("camera_position", camera.position);
		mesh.Render(camera);

		lightBox.position = glm::vec3(light_position);
		lightBox.Render(camera);
		frameCtr++;

		if (aggr > 5)
		{
			frames = frameCtr / 5.0;
			frameCtr = 0;
			aggr = 0;
			std::cout << "the frame count is " << frames << " per second" << std::endl;
		}

		glfwSwapBuffers(window.ref);
		glfwPollEvents();
	}

	// mesh.Delete();
	window.Delete();
	glfwTerminate();
	return 0;
}

