#include "Light.h"

Light::Light(glm::vec3 position) : position(position)
{
}

void Light::Export(Shader& shader)
{
	shader.Activate();
	shader.SetVec3("light.position", position);

	shader.SetVec3("light.ambient", ambient);
	shader.SetVec3("light.diffuse", diffuse);
	shader.SetVec3("light.specular", specular);
}
