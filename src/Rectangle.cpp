#include <glm/glm.hpp>
#include <vector>
#include <model/Mesh.h>

std::vector<Vertex> vertices = {
    //             Position            // Normal  //    Color   //    texUV    //
    Vertex{glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(), glm::vec3(), glm::vec2(1, 1)}, // top right
    Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(), glm::vec3(), glm::vec2(1, 0)}, // bottom right
    Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(), glm::vec3(), glm::vec2(0, 0)}, // bottom left
    Vertex{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(), glm::vec3(), glm::vec2(0, 1)} // top left 
};

std::vector<unsigned int> indices = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};
