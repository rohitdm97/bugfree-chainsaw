#pragma once
#ifndef __VAO_CLASS_H
#define __VAO_CLASS_H

#include <glad/glad.h>

#include "VBO.h"
#include "EBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !__VAO_CLASS_H
