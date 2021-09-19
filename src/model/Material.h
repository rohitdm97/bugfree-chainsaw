#pragma once
#ifndef __MATERIAL_CLASS_h
#define __MATERIAL_CLASS_h

#include <glm/glm.hpp>
#include <memory>

#include <render/Shader.h>
#include <texture/Texture.h>

typedef std::unique_ptr<Texture> TexturePtr;

class Material
{
private:
	bool applicable;
public:
	TexturePtr texture;
	glm::vec3 specular;
	float shininess;
	Material();
	Material(const char* texture);

	void Export(Shader& shader);
};

#endif // !__MATERIAL_CLASS_h

