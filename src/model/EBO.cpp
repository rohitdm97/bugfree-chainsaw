#include "EBO.h"
#include <debug.h>

EBO::EBO(std::vector<unsigned int>& indices)
{
	Length = indices.size();
	glGenBuffers(1, &ID);
	EBO::Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

EBO::~EBO()
{
	EBO::Unbind();
	glDeleteBuffers(1, &ID);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

