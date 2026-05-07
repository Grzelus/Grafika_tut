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


struct Kitty {
    std::vector<glm::vec3> path;
    int targetIdx = 0;
    float speed;
    float waitTime;
    float timer = 0.0f;
    bool isWaiting = false;
    glm::vec3 pos;

    Kitty(std::vector<glm::vec3> p, float s, float w)
        : path(p), speed(s), waitTime(w), pos(p[0]) {
    }

    glm::vec3 update(float deltaTime) {
        if (isWaiting) {
            timer += deltaTime;
            if (timer >= waitTime) {
                isWaiting = false;
                timer = 0.0f;
                targetIdx = (targetIdx + 1) % path.size();
            }
        }
        else {
            glm::vec3 target = path[targetIdx];
            float dist = glm::distance(pos, target);

            if (dist < deltaTime * speed) {
                pos = target;
                isWaiting = true;
            }
            else {
                pos += glm::normalize(target - pos) * speed * deltaTime;
            }
        }
        return pos;
    }
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct TextureData {
    GLuint id;
    Material mat;
};

struct MainShaderLocs {
    GLint camMatrix;
    GLint model;
    GLint cameraPos;
    GLint lightColor;
    GLint lightPos;
    GLint color; // Dodano color
     
    GLint tex0=0;
	GLint SpecularMap = 1;
    GLint useSpecularMap;
    GLint texScale;
    GLint texShift;
    GLint texRotation;
    struct {
        GLint ambient;
        GLint diffuse;
        GLint specular;
        GLint shininess;
    } material;
    MainShaderLocs(Shader& shader) {
        tex0=glGetUniformLocation(shader.ID, "tex0");
        SpecularMap=glGetUniformLocation(shader.ID, "SpecularMap");
        model = glGetUniformLocation(shader.ID, "model");
        texScale = glGetUniformLocation(shader.ID, "texScale");
        texShift = glGetUniformLocation(shader.ID, "texShift");
        texRotation = glGetUniformLocation(shader.ID, "texRotation");
        useSpecularMap = glGetUniformLocation(shader.ID, "useSpecularMap");
        material.ambient = glGetUniformLocation(shader.ID, "material.ambient");
        material.diffuse = glGetUniformLocation(shader.ID, "material.diffuse");
        material.specular = glGetUniformLocation(shader.ID, "material.specular");
        material.shininess = glGetUniformLocation(shader.ID, "material.shininess");
        lightPos = glGetUniformLocation(shader.ID, "lightPos");
        cameraPos = glGetUniformLocation(shader.ID, "cameraPos");
        color = glGetUniformLocation(shader.ID, "color");
        lightColor = glGetUniformLocation(shader.ID, "lightColor");
    }
};

struct objectToRender {
	Model* model;
    TextureData* textureData;
    glm::vec3 position;
    glm::vec3 rotations = glm::vec3(0.0f, 0.0f, 0.0f);
    float scale = 1.0f;
    float texScale = 1.0f;
};

// --- STA£E I DANE ---
const float width = 800.0f;
const float height = 800.0f;

//headers of functions
GLFWwindow* setupWindow(int w, int h, const char* title);
GLuint setupTexture(const char* path);
void texCheck(GLuint texture, const char* path);
void renderScene(Shader& shaderProgram, Shader& shaderLight, Camera& camera, std::map<std::string, Model>& models, std::map<std::string, TextureData>& textures, const MainShaderLocs& mainLocs, glm::vec3 kittyPos, glm::vec3 kittyPos2);

// --- FUNKCJE POMOCNICZE ---

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
    models.emplace("walls", std::move(walls));

    Model floor("assets/floor.obj");
    models.emplace("floor", std::move(floor));

    Model display("assets/display.obj");
    models.emplace("display", std::move(display));

    Model frame("assets/frame.obj");
    models.emplace("frame", std::move(frame));

    Model painting("assets/painting.obj");
    models.emplace("painting", std::move(painting));

    Model frame_001("assets/frame.obj");
    models.emplace("frame_001", std::move(frame_001));

    Model painting_001("assets/painting.obj");
    models.emplace("painting_001", std::move(painting_001));

    Model frame_002("assets/frame.obj");
    models.emplace("frame_002", std::move(frame_002));

    Model painting_002("assets/painting.obj");
    models.emplace("painting_002", std::move(painting_002));

    Model frame_003("assets/frame.obj");
    models.emplace("frame_003", std::move(frame_003));

    Model painting_003("assets/painting.obj");
    models.emplace("painting_003", std::move(painting_003));

    Model painting_004("assets/painting.obj");
    models.emplace("painting_004", std::move(painting_004));

    Model frame_004("assets/frame.obj");
    models.emplace("frame_004", std::move(frame_004));

    Model painting_005("assets/painting.obj");
    models.emplace("painting_005", std::move(painting_005));

    Model frame_005("assets/frame.obj");
    models.emplace("frame_005", std::move(frame_005));

    Model painting_006("assets/painting.obj");
    models.emplace("painting_006", std::move(painting_006));

    Model frame_006("assets/frame.obj");
    models.emplace("frame_006", std::move(frame_006));

    Model torso("assets/torso.obj");
    models.emplace("torso", std::move(torso));

    Model stand("assets/stand.obj");
    models.emplace("stand", std::move(stand));

    Model fance("assets/fance.obj");
    models.emplace("fance", std::move(fance));

    Model abstractfigure("assets/abstractfigure.obj");
    models.emplace("abstractfigure", std::move(abstractfigure));


    // kotki
    Model kitty_head("assets/kitty_head.obj");
    models.emplace("kitty_head", std::move(kitty_head));
    
    Model kitty_dress("assets/kitty_dress.obj");
    models.emplace("kitty_dress", std::move(kitty_dress));

    Model kitty_head2("assets/kitty_head.obj");
	models.emplace("kitty_head2", std::move(kitty_head2));
	
    Model kitty_dress2("assets/kitty_dress.obj");
	models.emplace("kitty_dress2", std::move(kitty_dress2));


    // LAMPY / KLOSZE
    Model shade_top("assets/shade_top.obj");
    models.emplace("shade_top", std::move(shade_top));

    Model shade_top_001("assets/shade_top.obj");
    models.emplace("shade_top_001", std::move(shade_top_001));

    Model shade_top_002("assets/shade_top.obj");
    models.emplace("shade_top_002", std::move(shade_top_002));

    Model shade_top_003("assets/shade_top.obj");
    models.emplace("shade_top_003", std::move(shade_top_003));
	
    // ¿arówki w pêtli
    std::vector<glm::vec3> bulbPos = GetBulbPositions();
    for (size_t i = 0; i < bulbPos.size(); ++i) {
        std::string name = "bulb" + (i == 0 ? "" : "_00" + std::to_string(i));
        Model b("assets/bulb.obj");
        models.emplace(name, std::move(b));
        models.at(name).Transform(bulbPos[i], glm::vec3(0.0f));
    }
    
    Model celling("assets/celling.obj");
    models.emplace("celling", std::move(celling));

    std::cout << "dziala koniec wczytywania modeli" << std::endl;
    return models;
}

static std::map<std::string, Material> LoadAllMaterials() {
    std::map<std::string, Material> materials;

    // Drewno - matowe, niskie odbicie œwiat³a
    materials["wood"] = {
        glm::vec3(0.2f, 0.15f, 0.1f),   // ambient
        glm::vec3(0.6f, 0.4f, 0.2f),    // diffuse
        glm::vec3(0.1f, 0.1f, 0.1f),    // specular
        16.0f                           // shininess
    };

    // Metal - wysokie odbicie (specular) i po³ysk
    materials["metal"] = {
        glm::vec3(0.25f, 0.25f, 0.25f),
        glm::vec3(0.4f, 0.4f, 0.4f),
        glm::vec3(0.77f, 0.77f, 0.77f),
        76.8f
    };

    // Œciana - bardzo matowa, równe i jasne rozproszenie
    materials["wall"] = {
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(0.05f, 0.05f, 0.05f),
        8.0f
    };

    // Kamieñ - poch³ania du¿o œwiat³a, lekko matowy
    materials["stone"] = {
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        10.0f
    };

    // P³ótno (canvas) - bardzo niska b³yszcz¹coœæ, dobrze rozprasza œwiat³o
    materials["canvas"] = {
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.01f, 0.01f, 0.01f),
        2.0f
    };
    
    // Plastik - uniwersalny materia³ z umiarkowanym odbiciem
    materials["plastic"] = {
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        32.0f
    };
    
    // Domyœlny materia³ zapasowy
    materials["default"] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        32.0f
    };

    return materials;
}

static std::map<std::string, TextureData> LoadAllTextures() {
    std::map<std::string, TextureData> textures;
    auto materials = LoadAllMaterials(); // Pobranie zdefiniowanych materia³ów

    std::cout << "dziala wczytywanie tekstur" << std::endl;

    textures.emplace("dirt", TextureData{ setupTexture("assets/textures/dirt.jpg"), materials["stone"] });
    textures.emplace("wall", TextureData{ setupTexture("assets/textures/wallTex2.jpg"), materials["wall"] });
    textures.emplace("floor", TextureData{ setupTexture("assets/textures/floorTex2.jpg"), materials["wood"] });
    
    // Obrazy (P³ótno)
    textures.emplace("painting1", TextureData{ setupTexture("assets/textures/painting1.jpg"), materials["canvas"] });
    textures.emplace("painting2", TextureData{ setupTexture("assets/textures/painting2.jpg"), materials["canvas"] });
    textures.emplace("painting3", TextureData{ setupTexture("assets/textures/painting3.jpg"), materials["canvas"] });
    textures.emplace("painting4", TextureData{ setupTexture("assets/textures/painting4.jpg"), materials["canvas"] });
    textures.emplace("painting5", TextureData{ setupTexture("assets/textures/painting5.jpg"), materials["canvas"] });
    textures.emplace("painting6", TextureData{ setupTexture("assets/textures/painting6.jpg"), materials["canvas"] });
    textures.emplace("painting7", TextureData{ setupTexture("assets/textures/painting7.jpg"), materials["canvas"] });
    
    // Ramy
    textures.emplace("frame", TextureData{ setupTexture("assets/textures/frame2Texture.jpg"), materials["wood"] });
    textures.emplace("frame2", TextureData{ setupTexture("assets/textures/woodenFrameTex.jpg"), materials["wood"] });
    
    // Ró¿ne
    textures.emplace("metal", TextureData{ setupTexture("assets/textures/metalTex2.jpg"), materials["metal"] });
    textures.emplace("white", TextureData{ setupTexture("assets/textures/whiteTex.jpg"), materials["plastic"] });
    textures.emplace("blackTexture", TextureData{ setupTexture("assets/textures/blackTex.jpg"), materials["plastic"] });
    textures.emplace("greyStone", TextureData{ setupTexture("assets/textures/greyStoneTex.png"), materials["stone"] });
    textures.emplace("kitty", TextureData{ setupTexture("assets/textures/kitty.jpg"), materials["canvas"] }); // Przyk³adowo canvas dla zmatowienia
    textures.emplace("specularFloor", TextureData{ setupTexture("assets/textures/floorTex2_specular.png"), materials["wood"] });

    std::cout << "dziala wczytywanie tekstur koniec" << std::endl;

    return textures;
}

static std::vector<objectToRender> LoadAllObjectsToRender(std::map<std::string, Model>& models, std::map<std::string, TextureData>& textures) {
    std::vector<objectToRender> objects;

    // Funkcja lambda u³atwiaj¹ca dodawanie obiektów (z parametrem scale wstawionym na koñcu)
    auto addObject = [&](const std::string& modelName, const std::string& texName, glm::vec3 pos, glm::vec3 rot = glm::vec3(0.0f), float texscale = 1.0f) {
        objectToRender obj;
		obj.model = &models.at(modelName);
		obj.textureData = &textures.at(texName);
		obj.position = pos;
		obj.rotations = rot;
		obj.texScale = texscale;
        objects.push_back(obj);
        };

    // Dodanie sta³ych elementów - ŒCIANY, WYSTAWY, POD£OGA (Skala z renderScene: 20.0f)
    addObject("walls", "wall", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), 20.0f);
    addObject("display", "wall", glm::vec3(0.0f, 0.0f, 2.899f), glm::vec3(0.0f), 20.0f);
    addObject("floor", "floor", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), 20.0f);
    
    // RAMA I OBRAZ FRONTOWY
    addObject("frame", "frame2", glm::vec3(0.0f, 1.077f, 2.768f), glm::vec3(0.0f), 2.0f);
    addObject("painting", "painting1", glm::vec3(0.0f, 1.077f, 2.603f), glm::vec3(0.0f), 2.5f);

    // RAMY I OBRAZY (Prawe/lewe/tylne)
    // Ramy mia³y skalê tekstury 2.0f, obrazy boczne 3.0f w starym renderScene
    addObject("frame_001", "frame2", glm::vec3(13.372f, 1.068f, -13.821f), glm::vec3(0.0f, 3.142f, 0.0f), 2.0f);
    addObject("painting_001", "painting2", glm::vec3(13.372f, 1.068f, -13.656f), glm::vec3(0.0f, 3.142f, 0.0f), 3.0f);

    addObject("frame_002", "frame2", glm::vec3(9.744f, 1.068f, -9.438f), glm::vec3(0.0f, 4.712f, 0.0f), 2.0f);
    addObject("painting_002", "painting3", glm::vec3(9.909f, 1.068f, -9.438f), glm::vec3(0.0f, 4.712f, 0.0f), 3.0f);

    addObject("frame_003", "frame2", glm::vec3(17.000f, 1.068f, -9.400f), glm::vec3(0.0f, 1.571f, 0.0f), 2.0f);
    addObject("painting_003", "painting4", glm::vec3(16.835f, 1.068f, -9.400f), glm::vec3(0.0f, 1.571f, 0.0f), 3.0f);

    addObject("frame_004", "frame2", glm::vec3(17.000f, 1.068f, -3.349f), glm::vec3(0.0f, 1.571f, 0.0f), 2.0f);
    addObject("painting_004", "painting5", glm::vec3(16.835f, 1.068f, -3.349f), glm::vec3(0.0f, 1.571f, 0.0f), 3.0f);

    addObject("frame_005", "frame2", glm::vec3(17.000f, 1.068f, 2.248f), glm::vec3(0.0f, 1.571f, 0.0f), 2.0f);
    addObject("painting_005", "painting6", glm::vec3(16.835f, 1.068f, 2.248f), glm::vec3(0.0f, 1.571f, 0.0f), 3.0f);

    addObject("frame_006", "frame2", glm::vec3(13.300f, 1.068f, 5.779f), glm::vec3(0.0f), 2.0f);
    addObject("painting_006", "painting7", glm::vec3(13.300f, 1.068f, 5.614f), glm::vec3(0.0f), 3.0f);

    // INNE ELEMENTY WYSTAWOWE (Skala zostaje domyœlna 1.0f)
    addObject("torso", "white", glm::vec3(14.012f, 0.447f, -18.300f));
    addObject("stand", "greyStone", glm::vec3(14.034f, 0.000f, -18.300f));
    addObject("fance", "metal", glm::vec3(14.012f, 0.470f, -18.300f));
    addObject("abstractfigure", "metal", glm::vec3(-1.026f, 1.097f, -18.333f)); 

    // KLOSZE LAMP (Domyœlna skala 1.0f)
    addObject("shade_top", "metal", glm::vec3(0.0f, 2.030f, -0.401f));
    addObject("shade_top_001", "metal", glm::vec3(0.0f, 2.023f, -16.322f));
    addObject("shade_top_002", "metal", glm::vec3(13.372f, 3.304f, -5.521f));
    addObject("shade_top_003", "metal", glm::vec3(13.372f, 3.304f, -0.615f));

    // SUFIT (Domyœlna skala 1.0f)
    addObject("celling", "wall", glm::vec3(0.0f, 0.0f, 0.0f));

    return objects;
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

void renderScene2(Shader& shaderProgram,const MainShaderLocs& mainLocs, const std::vector<objectToRender>& objects) {
    auto setMaterial = [&](const Material& mat) {
        glUniform3fv(mainLocs.material.ambient, 1, glm::value_ptr(mat.ambient));
        glUniform3fv(mainLocs.material.diffuse, 1, glm::value_ptr(mat.diffuse));
        glUniform3fv(mainLocs.material.specular, 1, glm::value_ptr(mat.specular));
        glUniform1f(mainLocs.material.shininess, mat.shininess);
        };
    glActiveTexture(GL_TEXTURE0);
    for (auto& objectToRender : objects) {
        
        // Przekazanie transformacji, w tym pozycji i rotacji
        objectToRender.model->Transform(objectToRender.position, objectToRender.rotations);

        // Przekazanie skali (jeœli model klasyczny obs³uguje oddzieln¹ skalê w rysowaniu / b¹dŸ jako texScale)
        glUniform1f(mainLocs.texScale, objectToRender.texScale);
        
        // Zwi¹zanie tekstury i materia³u
		glBindTexture(GL_TEXTURE_2D, objectToRender.textureData->id);

        setMaterial(objectToRender.textureData->mat);
        
        // Rysowanie
		objectToRender.model->Draw(shaderProgram);
    }
}


void renderAudience(Shader& shaderProgram, const MainShaderLocs& mainLocs, std::map<std::string, Model>& models, std::map<std::string, TextureData>& textures, glm::vec3 kittyPos1, glm::vec3 kittyPos2) {
    // Resetowanie przesuniêæ i obrotów tekstur na domyœlne (jeœli we wczeœniejszym wywo³aniu jakieœ by³y zmieniane)
    glUniform1f(mainLocs.texScale, 1.0f);
    glUniform1f(mainLocs.texRotation, 0.0f);
    glUniform2f(mainLocs.texShift, 0.0f, 0.0f);

    // Lambda pomocnicza do ustawiania materia³u (podobnie jak dla statyków)
    auto setMaterial = [&](const Material& mat) {
        glUniform3fv(mainLocs.material.ambient, 1, glm::value_ptr(mat.ambient));
        glUniform3fv(mainLocs.material.diffuse, 1, glm::value_ptr(mat.diffuse));
        glUniform3fv(mainLocs.material.specular, 1, glm::value_ptr(mat.specular));
        glUniform1f(mainLocs.material.shininess, mat.shininess);
        };

    // --- KOTEK 1 ---
    // Ustawienia tekstury i materia³u kotka
    glBindTexture(GL_TEXTURE_2D, textures.at("kitty").id);
    setMaterial(textures.at("kitty").mat);

    glm::vec3 kittyRotation1 = glm::vec3(0.0f, 3.142f, 0.0f);

    // G³owa z wektorem offsetu wysokoœci
    models.at("kitty_head").Transform(kittyPos1 + glm::vec3(0.0f, 0.479f, 0.0f), kittyRotation1);
    models.at("kitty_head").Draw(shaderProgram);

    // Cia³o (sukienka)
    models.at("kitty_dress").Transform(kittyPos1, kittyRotation1);
    models.at("kitty_dress").Draw(shaderProgram);


    // --- KOTEK 2 ---
    // Podobnie u¿ywamy tej samej podpiêtej tekstury, tylko innych modeli
    glm::vec3 kittyRotation2 = glm::vec3(0.0f, 4.712f, 0.0f);

    models.at("kitty_head2").Transform(kittyPos2 + glm::vec3(0.0f, 0.479f, 0.0f), kittyRotation2);
    models.at("kitty_head2").Draw(shaderProgram);

    models.at("kitty_dress2").Transform(kittyPos2, kittyRotation2);
    models.at("kitty_dress2").Draw(shaderProgram);
}

// --- MAIN ---
int main() {
    GLFWwindow* window = setupWindow(800, 800, "Art Galery");
    if (!window) return -1;

    Shader shaderProgram("default.vert", "default.frag");
    Shader shaderLight("light.vert", "light.frag");
    
	//loading neccersary data
    auto models = LoadAllModels();
    auto textures = LoadAllTextures();
	auto objectsToRender = LoadAllObjectsToRender(models, textures);
    
    shaderProgram.Activate();
    shaderProgram.compileErrors(shaderProgram.ID,"PROGRAM");

    MainShaderLocs mainLocs(shaderProgram);
    

    static std::vector<glm::vec3> lightPositions = GetBulbPositions();
    glUniform3fv(mainLocs.lightPos, 4, glm::value_ptr(lightPositions[0]));

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));

    // Ustawienia dla shaderLight
    shaderLight.Activate();
    shaderLight.compileErrors(shaderLight.ID, "Light");

    GLuint lightModel=glGetUniformLocation(shaderLight.ID, "model");
    GLuint lightColorL = glGetUniformLocation(shaderLight.ID, "lightColor");
    
    std::vector<glm::vec3> kittyPath = {
        glm::vec3(11.11f, 0.0f, -18.3f),
        glm::vec3(7.912f, 0.0f, -18.3f),
        glm::vec3(7.912f, 0.0f, 1.6f),
        glm::vec3(13.61f, 0.0f, 1.6f),
        glm::vec3(13.61f, 0.0f, -10.5f),
        glm::vec3(11.00f, 0.0f, -9.5f),
        glm::vec3(11.00f, 0.0f, 1.6f),
        glm::vec3(8.912f, 0.0f, 1.6f),
        glm::vec3(8.912f, 0.0f, -18.3f),
    };

    std::vector<glm::vec3> kittyPath2 = {
        glm::vec3(-1.0f, 0.0f, -17.0f),
        glm::vec3(11.0f, 0.0f, -17.0f),
        glm::vec3(7.0f, 0.0f, -17.0f),
        glm::vec3(7.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 1.3f)   
    };

    Kitty kitty1(kittyPath, 2.0f, 1.0f);
    Kitty kitty2(kittyPath2, 2.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.1f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();
        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram.Activate();
        camera.Matrix(shaderProgram, "camMatrix");
        glUniform3f(mainLocs.cameraPos, camera.Position.x, camera.Position.y, camera.Position.z);

        glActiveTexture(GL_TEXTURE0);
        glUniform4f(mainLocs.color, 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform1f(mainLocs.texRotation, 0.0f);
        glUniform1f(mainLocs.texScale, 1.0f);
        glUniform2f(mainLocs.texShift, 0.0f, 0.0f);
        glUniform1i(mainLocs.useSpecularMap, 0);
        glUniform4f(mainLocs.lightColor, 1.0f, 0.9f, 0.9f, 1.0f);
      
        shaderLight.Activate();
        camera.Matrix(shaderLight, "camMatrix");
        glUniform4f(lightColorL, 1.0f, 1.0f, 1.0f, 1.0f);

        float crntTime = glfwGetTime();
        static float prevTime = 0.0f;
        float deltaTime = crntTime - prevTime;
        prevTime = crntTime;

        glm::vec3 pos1 = kitty1.update(deltaTime);
        glm::vec3 pos2 = kitty2.update(deltaTime);

        shaderProgram.Activate();
		renderScene2(shaderProgram, mainLocs, objectsToRender);
     //   renderScene(shaderProgram, shaderLight, camera, models, textures, mainLocs, pos1, pos2);
        renderAudience(shaderProgram, mainLocs, models, textures, pos1, pos2);

        shaderLight.Activate();
        camera.Matrix(shaderLight, "camMatrix");
        glUniform4f(lightColorL, 1.0f, 1.0f, 1.0f, 1.0f);
        models.at("bulb").Draw(shaderLight);
        models.at("bulb_001").Draw(shaderLight);
        models.at("bulb_002").Draw(shaderLight);
        models.at("bulb_003").Draw(shaderLight);

        glfwSwapBuffers(window);
    }

    shaderLight.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
