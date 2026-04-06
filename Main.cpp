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

// --- LADOWANIE I TRANSFORMACJA MODELI ---
    Model walls("assets/walls.obj");
    walls.Transform(glm::vec3(0.000f, 0.000f, -0.000f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model floor("assets/floor.obj");
    floor.Transform(glm::vec3(0.000f, 0.000f, -0.000f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model display("assets/display.obj");
    display.Transform(glm::vec3(0.000f, 0.000f, 2.899f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model frame("assets/frame.obj");
    frame.Transform(glm::vec3(0.000f, 1.077f, 2.768f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model painting("assets/painting.obj");
    painting.Transform(glm::vec3(-0.000f, 1.077f, 2.603f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model frame_001("assets/frame.obj");
    frame_001.Transform(glm::vec3(13.372f, 1.068f, -13.821f), glm::vec3(0.000f, 3.142f, -0.000f));

    Model painting_001("assets/painting.obj");
    painting_001.Transform(glm::vec3(13.372f, 1.068f, -13.656f), glm::vec3(0.000f, 3.142f, -0.000f));

    Model frame_002("assets/frame.obj");
    frame_002.Transform(glm::vec3(9.744f, 1.068f, -9.438f), glm::vec3(0.000f, 4.712f, -0.000f));

    Model painting_002("assets/painting.obj");
    painting_002.Transform(glm::vec3(9.909f, 1.068f, -9.438f), glm::vec3(0.000f, 4.712f, -0.000f));

    Model frame_003("assets/frame.obj");
    frame_003.Transform(glm::vec3(17.000f, 1.068f, -9.400f), glm::vec3(0.000f, 1.571f, -0.000f));

    Model painting_003("assets/painting.obj");
    painting_003.Transform(glm::vec3(16.835f, 1.068f, -9.400f), glm::vec3(0.000f, 1.571f, -0.000f));

    Model painting_004("assets/painting.obj");
    painting_004.Transform(glm::vec3(16.835f, 1.068f, -3.349f), glm::vec3(0.000f, 1.571f, -0.000f));

    Model frame_004("assets/frame.obj");
    frame_004.Transform(glm::vec3(17.000f, 1.068f, -3.349f), glm::vec3(0.000f, 1.571f, -0.000f));

    Model painting_005("assets/painting.obj");
    painting_005.Transform(glm::vec3(16.835f, 1.068f, 2.248f), glm::vec3(0.000f, 1.571f, -0.000f));

    Model frame_005("assets/frame.obj");
    frame_005.Transform(glm::vec3(17.000f, 1.068f, 2.248f), glm::vec3(0.000f, 1.571f, -0.000f));

    Model painting_006("assets/painting.obj");
    painting_006.Transform(glm::vec3(13.300f, 1.068f, 5.614f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model frame_006("assets/frame.obj");
    frame_006.Transform(glm::vec3(13.300f, 1.068f, 5.779f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model torso("assets/torso.obj");
    torso.Transform(glm::vec3(14.012f, 0.447f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model stand("assets/stand.obj");
    stand.Transform(glm::vec3(14.034f, 0.000f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model fance("assets/fance.obj");
    fance.Transform(glm::vec3(14.012f, 0.470f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));

    Model abstractfigure("assets/abstractfigure.obj");
    abstractfigure.Transform(glm::vec3(-1.026f, 1.097f, -18.333f), glm::vec3(0.000f, 0.000f, -0.000f));






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

        // --- RYSOWANIE MODELI ---
        walls.Draw(shaderProgram);
        floor.Draw(shaderProgram);
        display.Draw(shaderProgram);
        frame.Draw(shaderProgram);
        painting.Draw(shaderProgram);
        frame_001.Draw(shaderProgram);
        painting_001.Draw(shaderProgram);
        frame_002.Draw(shaderProgram);
        painting_002.Draw(shaderProgram);
        frame_003.Draw(shaderProgram);
        painting_003.Draw(shaderProgram);
        painting_004.Draw(shaderProgram);
        frame_004.Draw(shaderProgram);
        painting_005.Draw(shaderProgram);
        frame_005.Draw(shaderProgram);
        painting_006.Draw(shaderProgram);
        frame_006.Draw(shaderProgram);
        torso.Draw(shaderProgram);
        stand.Draw(shaderProgram);
        fance.Draw(shaderProgram);
		abstractfigure.Draw(shaderProgram);
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Sprz¹tanie
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}