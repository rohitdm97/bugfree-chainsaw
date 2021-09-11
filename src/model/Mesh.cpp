#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	modelMatrix = glm::translate(glm::mat4(1), glm::vec3(0.1, -0.2, 0));
	shader = std::make_unique<Shader>("simple");

	vao = std::make_unique<VAO>();
	vao->Bind();

	vbo = std::make_unique<VBO>(vertices);
	ebo = std::make_unique<EBO>(indices);

	vbo->Attribute();
	vao->Unbind();
}

void Mesh::Render(Camera& camera)
{
	shader->Activate();
	vao->Bind();
	ebo->Bind();

	camera.Export(*shader);
	shader->SetMat4("model", modelMatrix);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::Delete()
{
	vao->Delete();
	vbo->Delete();
	ebo->Delete();
	shader->Delete();
}



