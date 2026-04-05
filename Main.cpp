#include "Model.h"
#include <stdexcept>
#include <string>
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
void renderScene( GLuint texture, Shader& shader, float Time, Camera& camera) {

   
 
    camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

}

// --- MAIN ---
int main() {
    GLFWwindow* window = setupWindow(800, 800, "YoutubeOpenGL");
    if (!window) return -1;

    Shader shaderProgram("default.vert", "default.frag");


    // LADOWANIE MODELI

    Model walls("assets/walls.obj");
    walls.Move(glm::vec3(0.000f, 0.000f, -0.000f));

    Model floor("assets/floor.obj");
    floor.Move(glm::vec3(0.000f, 0.000f, -0.000f));

    Model display("assets/display.obj");
    display.Move(glm::vec3(0.000f, 0.000f, 2.899f));

    Model frame("assets/frame.obj");
    frame.Move(glm::vec3(0.000f, 1.077f, 2.768f));

    Model painting("assets/painting.obj");
    painting.Move(glm::vec3(-0.000f, 1.077f, 2.603f));



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
        renderScene(texture, shaderProgram, Time, camera);

		frame.Draw(shaderProgram);
        walls.Draw(shaderProgram);
        floor.Draw(shaderProgram);
        painting.Draw(shaderProgram);
        display.Draw(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Sprz¹tanie
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}