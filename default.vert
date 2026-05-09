#version 330 core

// data received from VBO
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

// data send to frag shader
out vec3 Normal;
out vec2 texCoord;
out vec3 currentPosition;
out mat2 rotationMatrix;
out vec4 FragPosLightSpace;

uniform mat4 lightSpaceMatrix; // from light perspective
uniform float texRotation; // rotation of texture
uniform mat4 camMatrix; // data from camera perspective + view
uniform mat4 model;    // from model class rotation, position scale

void main()
{
    float s = sin(texRotation);
    float c = cos(texRotation);    
    rotationMatrix = mat2(c, -s, s, c);

    currentPosition = vec3(model*vec4(aPos,1.0f));  


    Normal = normalize(mat3(model) * aNormal); 
    texCoord = aTexCoord; 
    FragPosLightSpace = lightSpaceMatrix * vec4(currentPosition, 1.0);
    gl_Position = camMatrix * vec4(currentPosition, 1.0f);
}