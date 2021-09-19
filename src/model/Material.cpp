#include "Material.h"

void Material::Export(Shader& shader)
{
	shader.SetVec3("material.ambient", ambient);
	shader.SetVec3("material.diffuse", diffuse);
	shader.SetVec3("material.specular", specular);

	shader.SetFloat("material.shininess", shininess);
}
