#pragma once
#ifndef __LIGHT_CLASS_H
#define __LIGHT_CLASS_H

#include <glm/glm.hpp>
#include "Shader.h"

class Light
{
public:
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	Light(glm::vec3 position);

	void Export(Shader& shader);
};


#endif // !__LIGHT_CLASS_H

