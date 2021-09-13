#pragma once
#ifndef __TEXTURE_CLASS_H
#define __TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>

class Texture
{
private:
	GLuint ID;
public:
	Texture(const char* filename);
	void Bind();

	static void Init();
};

#endif // !__TEXTURE_CLASS_H

