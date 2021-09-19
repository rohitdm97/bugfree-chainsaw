#pragma once
#ifndef __EBO_CLASS_H
#define __EBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class EBO
{
public:
	GLuint ID;
	GLsizei Length;
	EBO(std::vector<unsigned int>& indices);
	~EBO();

	void Bind();
	void Unbind();
};

#endif // !__EBO_CLASS_H

