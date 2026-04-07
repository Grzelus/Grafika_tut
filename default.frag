#version 330 core

out vec4 FragColor;

// Odbieranie danych, które wypluł Vertex Shader
in vec3 Normal;
in vec2 texCoord;

uniform vec4 color;

// Nasza tekstura (np. ziemia, ściany itp.) połączona z jednostką teksturującą
uniform sampler2D tex0;
uniform float texScale=1.0f;
uniform vec2 texShift=vec2(0.0f,0.0f);


void main()
{
    //do tekstruy
    FragColor = texture(tex0, texCoord*texScale)*color ;
    // do koloru
   // FragColor = color;
}