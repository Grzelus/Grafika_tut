#version 330 core

// Odbieramy dane z VAO (zgodnie z VAO1.LinkAttrib)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

// Wysyłamy dane do Fragment Shadera
out vec3 Normal;
out vec2 texCoord;

// Zmienna wysyłana przez funkcję camera.Matrix()
uniform mat4 camMatrix;

void main()
{
    Normal = aNormal;
    texCoord = aTexCoord;
    
    // Nakładamy transformację kamery na pozycję wierzchołków
    gl_Position = camMatrix * vec4(aPos, 1.0f);
}