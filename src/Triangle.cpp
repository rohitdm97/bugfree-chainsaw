#include<glad/glad.h>
#include<glm/glm.hpp>
#include<vector>

std::vector<glm::vec3> triangleVertices1 =
{
	glm::vec3(-.75, -.4, 0.0f),
	glm::vec3(-.25, -.4, 0.0f),
	glm::vec3(-.5, .4, 0.0f)
};

std::vector<glm::vec3> triangleVertices2 =
{
	glm::vec3(.25, -.4, 0.0f),
	glm::vec3(.75, -.4, 0.0f),
	glm::vec3(.5, .4, 0.0f)
};

std::vector<unsigned int> triangleIndices1 =
{
	0, 1, 2
};

std::vector<unsigned int> triangleIndices2 =
{
	0, 1, 2
};

std::vector<glm::vec3> triangleVertices12 =
{
	glm::vec3(-.75, -.4, 0.0f),
	glm::vec3(-.25, -.4, 0.0f),
	glm::vec3(-.5, .4, 0.0f)
	,
	glm::vec3(.25, -.4, 0.0f),
	glm::vec3(.75, -.4, 0.0f),
	glm::vec3(.5, .4, 0.0f)
};

std::vector<unsigned int> triangleIndices12 =
{
	0, 1, 2
	,
	3, 4, 5
};


