#version 330 core

out vec4 FragColor;

// from vertex shader
in vec3 Normal;
in vec2 texCoord;
in vec3 currentPosition;
in mat2 rotationMatrix;

uniform vec4 color;

// textures
uniform sampler2D tex0;
uniform sampler2D specularMap;
uniform float texScale = 1.0f;
uniform vec2 texShift = vec2(0.0f,0.0f);
uniform float texRotation = 0.0f;
uniform bool useSpecularMap = false;

// lighting
uniform vec4 lightColor;
uniform vec3 lightPos[4];
uniform vec3 cameraPos;

struct Material {
     vec3 diffuse; 
     vec3 ambient;
     vec3 specular;
     float shininess;
};
uniform Material material;


vec4 calculateLighting(vec2 uv) {
    const float linear = 0.01f;
    const float quadratic = 0.012f;
    const float ambient = 0.30f;

    vec3 norm = normalize(Normal);
    float diffuse = 0.0f; 
    float totalspecular = 0.0f; 
    
    for (int i = 0; i < 4; i++)
    {
        vec3 lightVector = lightPos[i] - currentPosition;
        float distance = length(lightVector);
        float intensityOfLight = 1.0f / (1.0f + linear * distance + quadratic * (distance * distance)); 

        vec3 lightDirection = normalize(lightVector);
    
        diffuse += max(dot(norm, lightDirection), 0.0f) * intensityOfLight; 

        float specularLight = 0.50f;
        vec3 viewDirection = normalize(cameraPos - currentPosition);
        vec3 reflectionDirection = reflect(-lightDirection, norm);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f),material.shininess);

        totalspecular += specAmount * specularLight * intensityOfLight;
    }  
    
    if(useSpecularMap){
        totalspecular *= texture(specularMap, uv).r;
    }
    
    vec4 baseTextureColor = texture(tex0, uv);
    vec3 ambientDiffuseResult = (diffuse * material.diffuse) + (ambient * material.ambient);
    
    vec4 ambientDiffuseColor = baseTextureColor * vec4(ambientDiffuseResult, 1.0f) * lightColor;
    vec4 specularColor = totalspecular * lightColor*vec4(material.specular,1.0f); 
    
    return ambientDiffuseColor + specularColor;
}

void main()
{
    
    vec2 centeredTexCoord = texCoord - vec2(0.5f, 0.5f);
    vec2 uv = rotationMatrix * texScale * centeredTexCoord;   
    uv = uv + vec2(0.5f, 0.5f) + texShift; 

    FragColor = calculateLighting(uv);
}