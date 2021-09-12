#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <debug.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) :
	Mesh(vertices, indices, std::make_unique<Shader>("simple"))
{
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::unique_ptr<Shader> shader) :
	shader(std::move(shader))
{
	modelMatrix = glm::mat4(1);

	vao = std::make_unique<VAO>();
	vao->Bind();

	vbo = std::make_unique<VBO>(vertices);
	ebo = std::make_unique<EBO>(indices);

	vbo->Attribute();
	vao->Unbind();
}

void Mesh::Move(glm::vec3 dir)
{
	Mesh::position += dir;
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
	return glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), glm::vec3(scale));
}

void Mesh::Render(Camera& camera)
{
	shader->Activate();
	vao->Bind();
	ebo->Bind();

	camera.Export(*shader);
	shader->SetMat4("model",  Matrix());

	glDrawElements(GL_TRIANGLES, ebo->Length, GL_UNSIGNED_INT, 0);
}

void Mesh::Delete()
{
	vao->Delete();
	vbo->Delete();
	ebo->Delete();
	shader->Delete();
}



