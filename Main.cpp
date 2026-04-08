#include "Model.h"
#include <stdexcept>
#include <string>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "stb/stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

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

static std::map<std::string, Model> LoadAllModels() {
    std::map<std::string, Model> models;

    Model walls("assets/walls.obj");
    walls.Transform(glm::vec3(0.000f, 0.000f, -0.000f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("walls", std::move(walls));

    Model floor("assets/floor.obj");
    floor.Transform(glm::vec3(0.000f, 0.000f, -0.000f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("floor", std::move(floor));

    Model display("assets/display.obj");
    display.Transform(glm::vec3(0.000f, 0.000f, 2.899f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("display", std::move(display));

    Model frame("assets/frame.obj");
    frame.Transform(glm::vec3(0.000f, 1.077f, 2.768f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("frame", std::move(frame));

    Model painting("assets/painting.obj");
    painting.Transform(glm::vec3(-0.000f, 1.077f, 2.603f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("painting", std::move(painting));

    Model frame_001("assets/frame.obj");
    frame_001.Transform(glm::vec3(13.372f, 1.068f, -13.821f), glm::vec3(0.000f, 3.142f, -0.000f));
    models.emplace("frame_001", std::move(frame_001));

    Model painting_001("assets/painting.obj");
    painting_001.Transform(glm::vec3(13.372f, 1.068f, -13.656f), glm::vec3(0.000f, 3.142f, -0.000f));
    models.emplace("painting_001", std::move(painting_001));

    Model frame_002("assets/frame.obj");
    frame_002.Transform(glm::vec3(9.744f, 1.068f, -9.438f), glm::vec3(0.000f, 4.712f, -0.000f));
    models.emplace("frame_002", std::move(frame_002));

    Model painting_002("assets/painting.obj");
    painting_002.Transform(glm::vec3(9.909f, 1.068f, -9.438f), glm::vec3(0.000f, 4.712f, -0.000f));
    models.emplace("painting_002", std::move(painting_002));

    Model frame_003("assets/frame.obj");
    frame_003.Transform(glm::vec3(17.000f, 1.068f, -9.400f), glm::vec3(0.000f, 1.571f, -0.000f));
    models.emplace("frame_003", std::move(frame_003));

    Model painting_003("assets/painting.obj");
    painting_003.Transform(glm::vec3(16.835f, 1.068f, -9.400f), glm::vec3(0.000f, 1.571f, -0.000f));
    models.emplace("painting_003", std::move(painting_003));

    Model painting_004("assets/painting.obj");
    painting_004.Transform(glm::vec3(16.835f, 1.068f, -3.349f), glm::vec3(0.000f, 1.571f, -0.000f));
    models.emplace("painting_004", std::move(painting_004));

    Model frame_004("assets/frame.obj");
    frame_004.Transform(glm::vec3(17.000f, 1.068f, -3.349f), glm::vec3(0.000f, 1.571f, -0.000f));
    models.emplace("frame_004", std::move(frame_004));

    Model painting_005("assets/painting.obj");
    painting_005.Transform(glm::vec3(16.835f, 1.068f, 2.248f), glm::vec3(0.000f, 1.571f, -0.000f));
    models.emplace("painting_005", std::move(painting_005));

    Model frame_005("assets/frame.obj");
    frame_005.Transform(glm::vec3(17.000f, 1.068f, 2.248f), glm::vec3(0.000f, 1.571f, -0.000f));
    models.emplace("frame_005", std::move(frame_005));

    Model painting_006("assets/painting.obj");
    painting_006.Transform(glm::vec3(13.300f, 1.068f, 5.614f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("painting_006", std::move(painting_006));

    Model frame_006("assets/frame.obj");
    frame_006.Transform(glm::vec3(13.300f, 1.068f, 5.779f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("frame_006", std::move(frame_006));

    Model torso("assets/torso.obj");
    torso.Transform(glm::vec3(14.012f, 0.447f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("torso", std::move(torso));

    Model stand("assets/stand.obj");
    stand.Transform(glm::vec3(14.034f, 0.000f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("stand", std::move(stand));

    Model fance("assets/fance.obj");
    fance.Transform(glm::vec3(14.012f, 0.470f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("fance", std::move(fance));

    Model abstractfigure("assets/abstractfigure.obj");
    abstractfigure.Transform(glm::vec3(-1.026f, 1.097f, -18.333f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("abstractfigure", std::move(abstractfigure));

    return models;
}




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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, wImg, hImg, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

static std::map<std::string, GLuint> LoadAllTextures() {
    std::map<std::string, GLuint> textures;

    GLuint dirtTexture = setupTexture("assets/textures/dirt.jpg");
    textures.emplace("dirt", std::move(dirtTexture));
    GLuint wallTexture = setupTexture("assets/textures/wallTex.jpg");
    textures.emplace("wall", std::move(wallTexture));
    GLuint floorTexture = setupTexture("assets/textures/floorTex.jpg");
    textures.emplace("floor", std::move(floorTexture));
    GLuint painting1Texture = setupTexture("assets/textures/painting1.jpg");
    textures.emplace("painting1", std::move(painting1Texture));
    GLuint painting2Texture = setupTexture("assets/textures/painting2.jpg");
    textures.emplace("painting2", std::move(painting2Texture));
    GLuint painting3Texture = setupTexture("assets/textures/painting3.jpg");
    textures.emplace("painting3", std::move(painting3Texture));
   GLuint painting4Texture = setupTexture("assets/textures/painting4.jpg");
    textures.emplace("painting4", std::move(painting4Texture));
    GLuint painting5Texture = setupTexture("assets/textures/painting5.jpg");
    textures.emplace("painting5", std::move(painting5Texture));
    GLuint painting6Texture = setupTexture("assets/textures/painting6.jpg");
    textures.emplace("painting6", std::move(painting6Texture));
    GLuint painting7Texture = setupTexture("assets/textures/painting7.jpg");
    textures.emplace("painting7", std::move(painting7Texture));
	GLuint frameTexture = setupTexture("assets/textures/frame2Texture.jpg"); 
	textures.emplace("frame", std::move(frameTexture));
	return textures;
}

void renderScene(Shader shaderProgram ,std::map<std::string, Model> models, std::map<std::string, GLuint> textures, GLuint texScale, GLuint texShift) {
    glUniform1f(texScale, 20.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("wall"));
    models.at("walls").Draw(shaderProgram);
    models.at("display").Draw(shaderProgram);

    glUniform1f(texScale, 20.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("floor"));
    models.at("floor").Draw(shaderProgram);


    glUniform1f(texScale, 25.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("frame"));
    models.at("frame").Draw(shaderProgram);
    models.at("frame_001").Draw(shaderProgram);
    models.at("frame_002").Draw(shaderProgram);
    models.at("frame_003").Draw(shaderProgram);
    models.at("frame_004").Draw(shaderProgram);
    models.at("frame_005").Draw(shaderProgram);
    models.at("frame_006").Draw(shaderProgram);

    //kazdy obraz inna tektura
    glUniform1f(texScale, 2.0f);
    glUniform2f(texShift, 0.5f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting1"));
    models.at("painting").Draw(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting2"));
    models.at("painting_001").Draw(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting3"));
    models.at("painting_002").Draw(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting4"));
    models.at("painting_003").Draw(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting5"));
    models.at("painting_004").Draw(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting6"));
    models.at("painting_005").Draw(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting7"));
    models.at("painting_006").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("dirt"));
    models.at("torso").Draw(shaderProgram);
    models.at("stand").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("floor"));
    models.at("fance").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("floor"));

    models.at("abstractfigure").Draw(shaderProgram);



}

// --- MAIN ---
int main() {
    GLFWwindow* window = setupWindow(800, 800, "YoutubeOpenGL");
    if (!window) return -1;

    Shader shaderProgram("default.vert", "default.frag");

    auto models = LoadAllModels();
    auto textures = LoadAllTextures();


    // Aktywacja shadera i przypisanie tekstury do samplera tex0
    shaderProgram.Activate();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 0);

	GLuint texScale = glGetUniformLocation(shaderProgram.ID, "texScale");
    GLuint texShift = glGetUniformLocation(shaderProgram.ID, "texShift");
    int colorLocation = glGetUniformLocation(shaderProgram.ID, "color");


	glEnable(GL_DEPTH_TEST);
    
	Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.1f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        camera.Inputs(window);

        float Time = glfwGetTime();
        // Wyrenderuj klatkê
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        glActiveTexture(GL_TEXTURE0);
        glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f);

		renderScene(shaderProgram,models, textures, texScale, texShift);  
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Sprz¹tanie
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}