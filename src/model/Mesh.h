#pragma once
#ifndef __MESH_CLASS_H
#define __MESH_CLASS_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VAO.h"
#include "render/Shader.h"

class Mesh
{
private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<VAO> vao;
	std::unique_ptr<VBO> vbo;
	std::unique_ptr<EBO> ebo;
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	void Render();
	void Delete();
};

#endif // !__MESH_CLASS_H

