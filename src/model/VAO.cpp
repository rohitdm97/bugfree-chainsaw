#include "VAO.h"
#include <debug.h>

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	INFO("VAO is generated");
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
