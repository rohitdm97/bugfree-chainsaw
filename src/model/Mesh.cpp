#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <debug.h>

#include <components/Camera.h>
#include <components/Light.h>

Mesh::Mesh(
	std::vector<Vertex>& vertices,
	std::vector<unsigned int>& indices,
	const char* shaderName
)
{
	Mesh::shader.reset(new Shader(shaderName));
	vao.reset(new VAO());
	vao->Bind();

	vbo.reset(new VBO(vertices));
	ebo.reset(new EBO(indices));

	vbo->Attribute();
	vao->Unbind();

	modelMatrix = glm::mat4(1);

	shader->Activate();

}

Mesh::~Mesh()
{
	ebo.reset();
	vbo.reset();
	vao.reset();

	shader.reset();
}

void Mesh::Move(glm::vec3 dir)
{
	Mesh::position += glm::vec4(dir, 1);
}

void Mesh::Scale(float mult)
{
	if (mult < 0.0) {
		mult = 1;
	}
	Mesh::scale *= mult;
}

glm::mat4 Mesh::Matrix()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(position));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(Mesh::scale));
	return translate * scale;
}

void Mesh::SetMaterial(Material& material)
{
	shader->Activate();
	material.Export(*shader);
}

void Mesh::Render(Camera& camera, Light& light)
{
	shader->Activate();
	vao->Bind();
	ebo->Bind();

	camera.Export(*shader);
	light.Export(*shader);
	shader->SetMat4("model",  Matrix());

	glDrawElements(GL_TRIANGLES, ebo->Length, GL_UNSIGNED_INT, 0);
}

