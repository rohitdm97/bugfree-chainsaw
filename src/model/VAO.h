#pragma once
#ifndef __VAO_CLASS_H
#define __VAO_CLASS_H

#include <glad/glad.h>

#include "VBO.h"
#include "EBO.h"

class VAO
{
private:

public:
	GLuint ID;

	VAO();
	~VAO();

	void Bind();
	void Unbind();
};

#endif // !__VAO_CLASS_H
