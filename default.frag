#version 330 core

out vec4 FragColor;

// Odbieranie danych, które wypluł Vertex Shader
in vec3 Normal;
in vec2 texCoord;

// Nasza tekstura (np. ziemia, ściany itp.) połączona z jednostką teksturującą
uniform sampler2D tex0;

void main()
{
    // Czytamy kolor z piksela tekstury
    FragColor = texture(tex0, texCoord);
}