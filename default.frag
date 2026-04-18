#version 330 core

out vec4 FragColor;

// from vertex shader
in vec3 Normal;
in vec2 texCoord;
in vec3 currentPosition;

uniform vec4 color;

// textures
uniform sampler2D tex0;
uniform float texScale=1.0f;
uniform vec2 texShift=vec2(0.0f,0.0f);
uniform float texRotation= 0.0f;

// lighting
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    //rotation of the texture
    float s = sin(texRotation);
    float c = cos(texRotation);    
    mat2 rotationMatrix = mat2(c, -s, s, c);//prepare rotation matrix

    vec2 centeredTexCoord = texCoord - vec2(0.5f, 0.5f);//center the coords to rotate around the center of the texture
    vec2 uv= rotationMatrix*texScale*centeredTexCoord;   //rotation and scaling
    uv=uv+vec2(0.5f,0.5f)+texShift; // getting back to the original position and applying shift 


    //lighting calculations
    float ambient = 0.20f; // ambient light factor
    vec3 norm = Normal;
    vec3 lightDirection =normalize(lightPos - currentPosition);
    
    float diffuse = max(dot(norm, lightDirection), 0.0f); 


    FragColor = texture(tex0,uv)*lightColor*(diffuse+ambient);
}