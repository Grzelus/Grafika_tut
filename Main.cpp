#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "stb/stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

#include<glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

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

// --- STA£E I DANE ---
const float width = 800.0f;
const float height = 800.0f;



// --- FUNKCJE POMOCNICZE ---

// 1. Inicjalizacja okna i bibliotek
GLFWwindow* setupWindow(int w, int h, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, w, h);
    return window;
}

// 2. Setup tekstury
GLuint setupTexture(const char* path) {
    GLuint texture;
    int wImg, hImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(path, &wImg, &hImg, &numColCh, 0);

    if (!bytes) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return 0;
    }

    GLint format = (numColCh == 4) ? GL_RGBA : GL_RGB;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, wImg, hImg, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}


// 4. Rysowanie obiektów
void renderScene(VAO& vao1, GLuint texture, Shader& shader, float Time, Camera& camera, int vertexCount) {

   
    vao1.Bind();

    camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);


    vao1.Unbind();
}

// --- MAIN ---
int main() {
    GLFWwindow* window = setupWindow(800, 800, "YoutubeOpenGL");
    if (!window) return -1;

    Shader shaderProgram("default.vert", "default.frag");

	std::vector<Vertex> paintingModel = loadModel("assets/painting.obj");


    // VAO1: Painting
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(paintingModel.data(), paintingModel.size() * sizeof(Vertex));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    VAO1.Unbind();

    

    GLuint texture = setupTexture("assets/dirt.jpg");

    // Aktywacja shadera i przypisanie tekstury do samplera tex0
    shaderProgram.Activate();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 0);

	glEnable(GL_DEPTH_TEST);
    
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.1f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        camera.Inputs(window);

        float Time = glfwGetTime();
        // Wyrenderuj klatkê
        renderScene(VAO1, texture, shaderProgram, Time, camera, paintingModel.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Sprz¹tanie
    VAO1.Delete(); VBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}