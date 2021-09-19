#pragma once
#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

#include <model/Mesh.h>
#include <render/Shader.h>
#include <texture/Texture.h>

#include <components/Light.h>
#include <components/Camera.h>

typedef std::unique_ptr<Camera> CameraPtr;
typedef std::unique_ptr<Light> LightPtr;
typedef std::unique_ptr<Mesh> MeshPtr;
typedef std::unique_ptr<Material> MaterialPtr;
typedef std::unique_ptr<Texture> TexturePtr;


class Model
{
public:
	CameraPtr camera;
	LightPtr light;
	MeshPtr mesh;
	MaterialPtr material;
	TexturePtr texture;

	Model(
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices,
		const char* shader,
		Material* material,
		Camera& camera,
		Light& light
	);

	void Move(glm::vec3 diff);

	void Update(double time, double d_time);
	void Render(double d_time);
};

#endif // !MODEL_CLASS_H

