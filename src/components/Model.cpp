#include "Model.h"

Model::Model(
	std::vector<Vertex>& vertices,
	std::vector<unsigned int>& indices,
	const char* shader,
	Material* material,
	Camera& camera,
	Light& light
)
{
	Model::camera.reset(&camera);
	Model::light.reset(&light);

	Model::mesh.reset(new Mesh(vertices, indices, shader));
	Model::material.reset(material);
	mesh->SetMaterial(*material);
}

void Model::Move(glm::vec3 diff)
{
	mesh->Move(diff);
}

void Model::Update(double time, double d_time)
{
}

void Model::Render(double d_time)
{
	mesh->Render(*camera, *light);
}
