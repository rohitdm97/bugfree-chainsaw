#pragma once
#ifndef __MATERIAL_CLASS_h
#define __MATERIAL_CLASS_h

#include <glm/glm.hpp>
#include "Shader.h"

class Material
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;
	Material();

	void Export(Shader& shader);
};

#endif // !__MATERIAL_CLASS_h

