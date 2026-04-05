#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"
#include "Model.h"
#include <stdexcept>
#include <string>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>


std::vector<Vertex> loadModel(const char* path) {
    std::vector<Vertex> vertices;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path)) {
        throw std::runtime_error(warn + err);
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex;

            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };
            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            };
            if (index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
                };
            };
            vertices.push_back(vertex);
        }
    }
    return vertices;
}


 
    Model::Model(const char* path) : verticies(loadModel(path)), vao(), vbo(verticies.data(), sizeof(Vertex)* verticies.size()) {
		modelMatrix = glm::mat4(1.0f);

        vao.Bind();
        vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
        vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

        vao.Unbind();
    }

    void Model::Draw(Shader& shader) {
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, verticies.size());
        vao.Unbind();
    }

    void Model::Move(glm::vec3 translation) {
		modelMatrix = glm::translate(modelMatrix, translation);
	}

    void Model::Delete() {
        vao.Delete();
        vbo.Delete();
    }

