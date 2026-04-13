#version 330 core

// Odbieranie danych z Twojego VBO (zgodnie z vao.LinkAttrib)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

// Zmienne wyrzucane dalej (do Fragment Shadera)
out vec3 Normal;
out vec2 texCoord;

// --- MACIERZE Z C++ ---
uniform mat4 camMatrix; // Wysyłana z klasy Camera (widok + perspektywa)
uniform mat4 model;     // Wysyłana z klasy Model (pozycja, rotacja, skala obiektu)

void main()
{
    // Przepisujemy normalne i koordynaty UV, żeby poleciały dalej
    Normal = aNormal;
    texCoord = aTexCoord;
    gl_Position = camMatrix * model * vec4(aPos, 1.0f);
}