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

GLFWwindow* setupWindow(int w, int h, const char* title);
GLuint setupTexture(const char* path);
void texCheck(GLuint texture, const char* path);
void renderScene(Shader& shaderProgram, Shader& shaderLight, Camera& camera, std::map<std::string, Model>& models, std::map<std::string, GLuint>& textures, GLuint texScale, GLuint texShift, GLuint texRotation);


// --- FUNKCJE POMOCNICZE ---
// Zwraca pozycje ¿arówek w galerii
static std::vector<glm::vec3> GetBulbPositions() {
    return {
        glm::vec3(-0.000f, 2.030f, -0.401f),  // bulb
        glm::vec3(-0.000f, 2.023f, -16.322f), // bulb_001
        glm::vec3(13.372f, 3.304f, -5.521f),  // bulb_002
        glm::vec3(13.372f, 3.304f, -0.615f)   // bulb_003
    };
}

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

    //tu jest rysowanie kotka

    Model kitty_head("assets/kitty_head.obj");
    kitty_head.Transform(glm::vec3(11.110f, 0.479f, -18.300f), glm::vec3(0.000f, 3.142f, -0.000f));
    models.emplace("kitty_head", std::move(kitty_head));

    Model kitty_nose("assets/kitty_nose.obj");
    kitty_nose.Transform(glm::vec3(11.110f, 0.702f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("kitty_nose", std::move(kitty_nose));

    Model kitty_dress("assets/kitty_dress.obj");
    kitty_dress.Transform(glm::vec3(11.110f, 0.000f, -18.300f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("kitty_dress", std::move(kitty_dress));


    //LAMPY
    //KLOSZE
    
    Model shade_top("assets/shade_top.obj");
    shade_top.Transform(glm::vec3(-0.000f, 2.030f, -0.401f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("shade_top", std::move(shade_top));

    Model shade_top_001("assets/shade_top.obj");
    shade_top_001.Transform(glm::vec3(-0.000f, 2.023f, -16.322f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("shade_top_001", std::move(shade_top_001));

    Model shade_top_002("assets/shade_top.obj");
    shade_top_002.Transform(glm::vec3(13.372f, 3.304f, -5.521f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("shade_top_002", std::move(shade_top_002));

    Model shade_top_003("assets/shade_top.obj");
    shade_top_003.Transform(glm::vec3(13.372f, 3.304f, -0.615f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("shade_top_003", std::move(shade_top_003));
	
    //wczytywanie ¿arówek w pêtli
    std::vector<glm::vec3> bulbPos = GetBulbPositions();
    for (size_t i = 0; i < bulbPos.size(); ++i) {
        std::string name = "bulb" + (i == 0 ? "" : "_00" + std::to_string(i));
        Model b("assets/bulb.obj");
        b.Transform(bulbPos[i], glm::vec3(0.0f));
        models.emplace(name, std::move(b));
    }
    Model celling("assets/celling.obj");
    celling.Transform(glm::vec3(0.000f, 0.000f, -0.000f), glm::vec3(0.000f, 0.000f, -0.000f));
    models.emplace("celling", std::move(celling));


    std::cout << "dziala koniec wczytywania modeli" << std::endl;
    return models;

}

static std::map<std::string, GLuint> LoadAllTextures() {
    std::map<std::string, GLuint> textures;


    std::cout << "dziala wczytywanie tekstur" << std::endl;

    GLuint dirtTexture = setupTexture("assets/textures/dirt.jpg");
    textures.emplace("dirt",dirtTexture);
    GLuint wallTexture = setupTexture("assets/textures/wallTex2.jpg");
    textures.emplace("wall", wallTexture);
    GLuint floorTexture = setupTexture("assets/textures/floorTex2.jpg");
    textures.emplace("floor", floorTexture);
    GLuint painting1Texture = setupTexture("assets/textures/painting1.jpg");
    textures.emplace("painting1", painting1Texture);
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
    GLuint metalTexture = setupTexture("assets/textures/metalTex2.jpg");
    textures.emplace("metal", std::move(metalTexture));
    GLuint white = setupTexture("assets/textures/whiteTex.jpg");
    textures.emplace("white", std::move(white));
    GLuint blackTexture = setupTexture("assets/textures/blackTex.jpg");//tesktura do zmiany 
    textures.emplace("blackTexture", std::move(blackTexture));
	GLuint frameTexture2 = setupTexture("assets/textures/woodenFrameTex.jpg");
    textures.emplace("frame2", std::move(frameTexture2));
    std::cout << "dziala wczytywanie tekstur koniec" << std::endl;

    return textures;
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
    if (texture == 0) std::cerr << "[setupTexture] glGenTextures returned 0 for " << path << std::endl;
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, wImg, hImg, 0, format, GL_UNSIGNED_BYTE, bytes);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "[setupTexture] GL error after teximage for " << path
            << ": 0x" << std::hex << err << std::dec << std::endl;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "[setupTexture] GL error after generateMipmap for " << path
            << ": 0x" << std::hex << err << std::dec << std::endl;
    }

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    std::cerr << "[setupTexture] OK: " << path << " -> tex=" << texture << std::endl;
    return texture;
}

void texCheck(GLuint texture, const char* path) {
    if (texture == 0) {
        std::cerr << "Failed to load texture: " << path << std::endl;
    } else {
        std::cerr << "Successfully loaded texture: " << path << " with ID: " << texture << std::endl;
    }
}



void renderScene(Shader& shaderProgram, Shader& shaderLight,Camera& camera,std::map<std::string, Model>& models, std::map<std::string, GLuint>& textures, GLuint texScale, GLuint texShift, GLuint texRotation) 
{
	shaderProgram.Activate();
    
    glUniform1f(texScale, 20.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("wall"));
    models.at("walls").Draw(shaderProgram);
    models.at("display").Draw(shaderProgram);

    glUniform1f(texScale, 20.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("floor"));
    models.at("floor").Draw(shaderProgram);


    glUniform1f(texScale, 25.0f);
    glBindTexture(GL_TEXTURE_2D, textures.at("frame2"));
    models.at("frame").Draw(shaderProgram);
    models.at("frame_001").Draw(shaderProgram);
    models.at("frame_002").Draw(shaderProgram);
    models.at("frame_003").Draw(shaderProgram);
    models.at("frame_004").Draw(shaderProgram);
    models.at("frame_005").Draw(shaderProgram);
    models.at("frame_006").Draw(shaderProgram);

    //kazdy obraz inna tektura
	//painting1 - obraz na scianie z przodu
    glUniform1f(texScale, 2.5f);
    glUniform2f(texShift, 1.0f, -0.2f);
    glBindTexture(GL_TEXTURE_2D, textures.at("painting1"));
    models.at("painting").Draw(shaderProgram);

	//pozostale obrazy - na scianie z prawej
    glUniform1f(texRotation, -1.6f);
	glUniform1f(texScale, 3.0f);
	glUniform2f(texShift, 0.9f, 0.0f);
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
    
    glBindTexture(GL_TEXTURE_2D, textures.at("white"));
    models.at("torso").Draw(shaderProgram);
    models.at("stand").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("metal"));
    models.at("fance").Draw(shaderProgram);
	models.at("abstractfigure").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("painting7")); //zmien teksture dla kazdego elementu plus napisz mi czy chcesz oczy
    models.at("kitty_head").Draw(shaderProgram);
    models.at("kitty_nose").Draw(shaderProgram);
    models.at("kitty_dress").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("metal")); // TU TAK SAMO
    models.at("shade_top").Draw(shaderProgram);
    models.at("shade_top_001").Draw(shaderProgram);
    models.at("shade_top_002").Draw(shaderProgram);
    models.at("shade_top_003").Draw(shaderProgram);

    glBindTexture(GL_TEXTURE_2D, textures.at("white")); // i tu <3
    models.at("celling").Draw(shaderProgram);

    shaderLight.Activate();
	
    models.at("bulb").Draw(shaderLight);
    models.at("bulb_001").Draw(shaderLight);
    models.at("bulb_002").Draw(shaderLight);
    models.at("bulb_003").Draw(shaderLight);

}
    // --- MAIN ---
    int main() {
        GLFWwindow* window = setupWindow(800, 800, "YoutubeOpenGL");
        if (!window) return -1;

        Shader shaderProgram("default.vert", "default.frag");
        Shader shaderLight("light.vert", "light.frag");

        auto models = LoadAllModels();
        auto textures = LoadAllTextures();

        // Aktywacja shadera i przypisanie tekstury do samplera tex0
        shaderProgram.Activate();
        shaderProgram.compileErrors(shaderProgram.ID,"PROGRAM");

        glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 0);
        GLuint texScale = glGetUniformLocation(shaderProgram.ID, "texScale");
        GLuint texShift = glGetUniformLocation(shaderProgram.ID, "texShift");
        GLuint texRotation = glGetUniformLocation(shaderProgram.ID, "texRotation");
        int colorLocation = glGetUniformLocation(shaderProgram.ID, "color");

        static std::vector<glm::vec3> lightPositions = GetBulbPositions();
        glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos"), 4, glm::value_ptr(lightPositions[0]));
        GLuint camPos = glGetUniformLocation(shaderProgram.ID, "cameraPos");
		GLuint lightColorP = glGetUniformLocation(shaderProgram.ID, "lightColor");



        glEnable(GL_DEPTH_TEST);

        Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));

		// Ustawienia dla shaderLight
        shaderLight.Activate();
        shaderLight.compileErrors(shaderLight.ID, "Light");

        GLuint lightModel=glGetUniformLocation(shaderLight.ID, "model");
		GLuint lightColorL = glGetUniformLocation(shaderLight.ID, "lightColor");
        
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.07f, 0.1f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            glfwPollEvents();
            camera.Inputs(window);
            camera.updateMatrix(45.0f, 0.1f, 100.0f);
            float Time = glfwGetTime();
            // Wyrenderuj klatkê


            shaderProgram.Activate();
            camera.Matrix(shaderProgram, "camMatrix");
            glUniform3f(camPos, camera.Position.x, camera.Position.y, camera.Position.z);

            glActiveTexture(GL_TEXTURE0);
            glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
            glUniform1f(texRotation, 0.0f);
            glUniform1f(texScale, 1.0f);
            glUniform2f(texShift, 0.0f, 0.0f);
            glUniform4f(lightColorP, 1.0f, 1.0f, 1.0f, 1.0f);

			shaderLight.Activate();
            camera.Matrix(shaderLight, "camMatrix");
            glUniform4f(lightColorL, 1.0f, 1.0f, 1.0f, 1.0f);

			renderScene(shaderProgram, shaderLight, camera ,models, textures, texScale, texShift, texRotation);
            glfwSwapBuffers(window);
            
        }

        // Sprz¹tanie
		shaderLight.Delete();
        shaderProgram.Delete();
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }