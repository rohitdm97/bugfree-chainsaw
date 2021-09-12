#include <glm/glm.hpp>
#include <vector>
#include <model/Mesh.h>

std::vector<Vertex> vertices = {
	//             Position            // Normal  //    Color   //    texUV    //
	Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1), glm::vec2(1, 1)}, // top right
	Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1), glm::vec2(1, 0)}, // bottom right
	Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1), glm::vec2(0, 0)}, // bottom left
	Vertex{glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1), glm::vec2(0, 1)} // top left 
	,
	Vertex{glm::vec3(0.5f,  0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), glm::vec2(0, 1)}, // top right
	Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), glm::vec2(0, 0)}, // bottom right
	Vertex{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), glm::vec2(1, 1)}, // top right
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), glm::vec2(1, 0)}, // bottom right

};

std::vector<unsigned int> indices = {
	0, 1, 3,
	1, 2, 3
	,
	4, 5, 7,
	4, 6, 7
};
