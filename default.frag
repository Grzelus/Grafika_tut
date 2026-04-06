#version 330 core

out vec4 FragColor;

// Odbieranie danych, które wypluł Vertex Shader
in vec3 Normal;
in vec2 texCoord;

uniform vec4 color;

// Nasza tekstura (np. ziemia, ściany itp.) połączona z jednostką teksturującą
uniform sampler2D tex0;

void main()
{
    //do tekstruy
    // FragColor = texture(tex0, texCoord);
    // do koloru
    FragColor = color;
}