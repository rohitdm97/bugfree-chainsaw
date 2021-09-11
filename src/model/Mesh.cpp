#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	shader = std::make_unique<Shader>("simple");

	vao = std::make_unique<VAO>();
	vao->Bind();

	vbo = std::make_unique<VBO>(vertices);
	ebo = std::make_unique<EBO>(indices);

	vbo->Attribute();
	vao->Unbind();
}

void Mesh::Render()
{
	shader->Activate();
	vao->Bind();
	ebo->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::Delete()
{
	vao->Delete();
	vbo->Delete();
	ebo->Delete();
	shader->Delete();
}



