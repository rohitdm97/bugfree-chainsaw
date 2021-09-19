#include "VAO.h"
#include <debug.h>

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	VAO::Unbind();
	glDeleteVertexArrays(1, &ID);
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

