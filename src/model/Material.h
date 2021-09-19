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
public:
	TexturePtr diffuse;
	TexturePtr specular;
	float shininess;
	Material();

	void Export(Shader& shader);
};

#endif // !__MATERIAL_CLASS_h

