#version 330 core

out vec4 FragColor;

// Odbieramy wartości z Vertex Shadera
in vec3 Normal;
in vec2 texCoord;

// Nasza tekstura przesyłana z C++
uniform sampler2D tex0;

void main()
{
    // Czytamy kolor z tekstury na podstawie koordynatów UV
    FragColor = texture(tex0, texCoord);
}