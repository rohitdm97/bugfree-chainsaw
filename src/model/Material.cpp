#include "Material.h"

Material::Material() {
	applicable = false;
}

Material::Material(const char* texture) {
	applicable = true;

	Material::texture.reset(new Texture(texture));
}

void Material::Export(Shader& shader)
{
	if (!applicable) {
		return ;
	}
	shader.SetInt("material.diffuse", 0);
	shader.SetVec3("material.specular", specular);

	shader.SetFloat("material.shininess", shininess);

	texture->Bind();
}
