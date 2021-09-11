#include "Texture.h"
#include <debug.h>

std::string convert(const char* filename) {
	return "textures/" + std::string(filename);
}

Texture::Texture(const char* filename)
{
	std::string filepath = convert(filename);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		ERROR("Failed to load the data");
	}

	glGenTextures(1, &ID);
	Texture::Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
