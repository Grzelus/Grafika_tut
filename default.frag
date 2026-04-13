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
uniform float texRotation= 0.0f;

void main()
{
    float s = sin(texRotation);
    float c = cos(texRotation);    
    mat2 rotationMatrix = mat2(c, -s, s, c);//prepare rotation matrix

    vec2 centeredTexCoord = texCoord - vec2(0.5f, 0.5f);//center the coords to rotate around the center of the texture
    vec2 uv= rotationMatrix*texScale*centeredTexCoord;   //rotation and scaling
    uv=uv+vec2(0.5f,0.5f)+texShift; // getting back to the original position and applying shift 

    FragColor = texture(tex0,uv)*color ;

}