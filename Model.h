#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include"VAO.h"
#include"VBO.h"
#include <vector>
#include "ShaderClass.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

std::vector<Vertex> loadModel(const char* path);

class Model {	
public:
	std::vector<Vertex> verticies;
	VAO vao;
	VBO vbo;
	glm::mat4 modelMatrix;
    Model(const char* path);

    void Draw(Shader& shader);

    void Transform(glm::vec3 translation, glm::vec3 rotation);

    void Delete();
};
#endif
