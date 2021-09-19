#pragma once
#ifndef __LIGHT_CLASS_H
#define __LIGHT_CLASS_H

#include <glm/glm.hpp>
#include <memory>

#include <model/Mesh.h>
#include <render/Shader.h>
#include <components/Camera.h>

typedef std::unique_ptr<Mesh> MeshPtr;

class Light
{
private:
// No-op for now
	Texture texture;

	Camera& camera;
public:
	// vec4 for easier calculations
	glm::vec4 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	MeshPtr mesh;

	Light(Mesh* mesh, Camera& camera);

	void Export(Shader& shader);
	void Update(double time, double delta);
	void Render(double delta);
};


#endif // !__LIGHT_CLASS_H

