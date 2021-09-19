#pragma once
#ifndef __VBO_CLASS_H
#define __VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 postion;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
private:
public:
	GLuint ID;

	VBO(std::vector<Vertex>& vertices);
	~VBO();

	// called by VAO
	void Attribute();

	void Bind();
	void Unbind();
};

#endif // !__VBO_CLASS_H

