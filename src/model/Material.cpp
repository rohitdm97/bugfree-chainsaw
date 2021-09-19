#include "Material.h"

Material::Material() {
}

void Material::Export(Shader& shader)
{
	shader.SetInt("material.diffuse", diffuse->slot);
	shader.SetInt("material.specular", specular->slot);

	shader.SetFloat("material.shininess", shininess);

	diffuse->Bind();
	specular->Bind();
}
