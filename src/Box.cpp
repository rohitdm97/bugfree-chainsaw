#include <glm/glm.hpp>
#include <vector>
#include <model/Mesh.h>

std::vector<Vertex> boxVertices = {
	//             Position            // Normal  //    Color   //    texUV    //
	Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(), glm::vec3(), glm::vec2()},
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(), glm::vec3(), glm::vec2()},
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(), glm::vec3(), glm::vec2()},
	Vertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(), glm::vec3(), glm::vec2()}
	,
	Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(), glm::vec3(), glm::vec2()},
	Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(), glm::vec3(), glm::vec2()},
	Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(), glm::vec3(), glm::vec2()},
	Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(), glm::vec3(), glm::vec2()}
};

std::vector<unsigned int> boxIndices = {
	0, 1, 3,
	1, 2, 3
	,
	4, 5, 7,
	5, 6, 7
	,
	0, 1, 4,
	1, 5, 4
	,
	1, 2, 5,
	2, 6, 5
	,
	3, 2, 7,
	2, 6, 7
	,
	0, 3, 4,
	3, 7, 4
};
