#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>

extern glm::vec3 origin;
extern glm::vec3 x_axis;
extern glm::vec3 y_axis;
extern glm::vec3 z_axis;

glm::vec3 rotation_axis = y_axis;
double generate_random_double(double time, double d_time);


Light::Light(Mesh* mesh, Camera& camera) : camera(camera)
{
	Light::position = mesh->position;
	Light::mesh.reset(mesh);
}

void Light::Export(Shader& shader)
{
	shader.Activate();
	shader.SetVec4("light.position", position);

	shader.SetVec3("light.ambient", ambient);
	shader.SetVec3("light.diffuse", diffuse);
	shader.SetVec3("light.specular", specular);
}

void Light::Update(double time, double delta)
{
	double d_theta = generate_random_double(time, delta);
	glm::mat4 rot = glm::rotate(glm::mat4(1), (float)d_theta, rotation_axis);
	position = rot * position;
}

void Light::Render(double delta)
{
	mesh->position = position;
	mesh->Render(camera, *this, texture);
}

double generate_random_double(double time, double d_time)
{
	double pi = 3.14159265;
	// theta = pi/8 * (2 + sin(2 pi f t))
	// d(theta) = pi/8 * (2 pi f cos(2 pi f t)) d(t)
	// f = 1/4
	// double theta = (pi / 8) * (2 * pi * (1.0/ 4) * cos(2 * pi * (1.0 / 4) * currentFrame) * delta);
	double f = 1.0 / 4;
	double span = pi / 4;
	double d_theta = d_time * span / 2.0 * (2 * pi * f * cos(2 * pi * f * time));

	return d_theta;
}

