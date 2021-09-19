#include "Engine.h"

#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include <window/Window.h>
#include <components/Model.h>

const int width = 1024;
const int height = 768;

extern std::vector<Vertex> vertices;
extern std::vector<unsigned int> indices;

extern std::vector<Vertex> boxVertices;
extern std::vector<unsigned int> boxIndices;

std::map<GLFWwindow*, Window*> Window::instances;

glm::vec3 origin = glm::vec3(0, 0, 0);
glm::vec3 x_axis = glm::vec3(1, 0, 0);
glm::vec3 y_axis = glm::vec3(0, 1, 0);
glm::vec3 z_axis = glm::vec3(0, 0, 1);

Material material = {
	glm::vec3(1.0f, 0.5f, 0.31f),
	glm::vec3(1.0f, 0.5f, 0.31f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	32.0f,
};

Engine::Engine() : metric(Metric(15))
{
	window.reset(new Window(width, height, "This is the title"));
	window->SetWireframe(false);
	if (window->ref == NULL) {
		window.reset();
		return ;
	}
	// activate the window and load openGL
	window->Activate();
	std::cout << "Created Window" << std::endl;

	camera.reset(new Camera(glm::vec3(5, 5, 5), width, height, -135, -35));
	window->SetCamera(camera);
	std::cout << "Created Camera" << std::endl;

	{
		Mesh* lightMesh = new Mesh(boxVertices, boxIndices, "light");
		lightMesh->Move(glm::vec3(
			glm::rotate(glm::mat4(1), glm::radians(45.0f), y_axis)
			*
			glm::vec4(0, 0, 2, 1)
		));
		lightMesh->Scale(0.05f);

		light.reset(new Light(lightMesh, *camera));
		light->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		light->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		light->specular = glm::vec3(1.0f, 1.0f, 1.0f);
		std::cout << "Created Light" << std::endl;
	}

	{
		model.reset(
			new Model(
				vertices, indices,
				"with_material",
				"wall.jpg",
				material,
				*camera,
				*light
			)
		);
		model->Move(glm::vec3(0.1, -0.2, 0));
		std::cout << "Created Model" << std::endl;
	}

}

Engine::~Engine()
{
	window.reset();
	camera.reset();
	light.reset();
	model.reset();

	glfwTerminate();
}

Engine::Engine(Engine& other) : metric(Metric(0))
{
	lastTime = other.lastTime;
	metric = other.metric;
	window = std::move(other.window);
}

Engine& Engine::operator=(Engine& other)
{
	if (this != &other) {
		lastTime = other.lastTime;
		metric = other.metric;
		window = std::move(other.window);
	}
	return *this;
}

void Engine::Start()
{
	if (!window) {
		std::cout << "Not starting the Engine. Window is not created" << std::endl;
		return ;
	}

	Run();
}

double Engine::getTime()
{
	return glfwGetTime();
}

void Engine::Run()
{
	Engine::lastTime = getTime();
	Engine::metric.deltaSum = 0;

	const double maxDelta = 1.0 / 120;
	double delta;
	while (!window->ShouldClose) {
		double thisTime = glfwGetTime();
		delta = thisTime - lastTime;
		lastTime = thisTime;

		window->HandleKeyboardInput(delta);
		while (delta > maxDelta) {
			Update(thisTime, maxDelta);
			delta -= maxDelta;
		}

		Render(delta);

		metric.Print();
		glfwPollEvents();
	}

	// this is hack
	exit(0);
}

void Engine::Update(double thisTime, double delta)
{
	model->Update(thisTime, delta);
	light->Update(thisTime, delta);

	metric.Update(delta);
}

void Engine::Render(double delta)
{
	glClearColor(0.17f, 0.45f, 0.87f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->Render(delta);
	light->Render(delta);

	metric.Render();
	glfwSwapBuffers(window->ref);
}
