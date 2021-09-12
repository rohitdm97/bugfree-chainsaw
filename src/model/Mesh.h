#pragma once
#ifndef __MESH_CLASS_H
#define __MESH_CLASS_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "VAO.h"
#include "render/Shader.h"
#include "camera/Camera.h"

class Mesh
{
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
private:
	std::unique_ptr<Shader> shader;
	std::unique_ptr<VAO> vao;
	std::unique_ptr<VBO> vbo;
	std::unique_ptr<EBO> ebo;

	float scale = 1.0f;
	glm::mat4 modelMatrix;

	glm::mat4 Matrix();
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::unique_ptr<Shader> shader);

	void Move(glm::vec3 dir);
	void Scale(float mult);
	void Render(Camera& camera);
	void Delete();
};

#endif // !__MESH_CLASS_H

