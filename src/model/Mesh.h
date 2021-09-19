#pragma once
#ifndef __MESH_CLASS_H
#define __MESH_CLASS_H

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <render/Shader.h>
#include <texture/Texture.h>

#include <model/VAO.h>
#include <model/VBO.h>
#include <model/EBO.h>
#include <model/Material.h>

class Camera;
class Light;

typedef std::unique_ptr<Shader> ShaderPtr;
typedef std::unique_ptr<VAO> VAOPtr;
typedef std::unique_ptr<VBO> VBOPtr;
typedef std::unique_ptr<EBO> EBOPtr;

class Mesh
{
public:
	glm::vec4 position = glm::vec4(0, 0, 0, 1);
private:
	ShaderPtr shader;
	VAOPtr vao;
	VBOPtr vbo;
	EBOPtr ebo;

	float scale = 1.0f;
	glm::mat4 modelMatrix;

	glm::mat4 Matrix();
public:
	Mesh(
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices,
		const char* shader
	);
	~Mesh();

	void Move(glm::vec3 dir);
	void Scale(float mult);
	void SetMaterial(Material& material);
	void Render(Camera& camera, Light& light);
	void Delete();
};

#endif // !__MESH_CLASS_H

