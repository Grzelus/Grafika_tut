#version 330 core

out vec4 FragColor;

// from vertex shader
in vec3 Normal;
in vec2 texCoord;
in vec3 currentPosition;

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

// ZMIANA: Zwracamy wektor vec4, który zawiera gotowy, oświetlony kolor
vec4 calculateLighting(vec2 uv) {
    const float linear = 0.1f;
    const float quadratic = 0.012f;
    const float ambient = 0.30f;

    vec3 norm = normalize(Normal);
    float diffuse = 0.0f; 
    float totalspecular = 0.0f; 
    
    for (int i = 0; i < 4; i++)
    {
        vec3 lightVector = lightPos[i] - currentPosition;
        float distance = length(lightVector);
        // Poprawiona literówka: intensity
        float intensityOfLight = 1.0f / (1.0f + linear * distance + quadratic * (distance * distance)); 

        vec3 lightDirection = normalize(lightVector);
    
        diffuse += max(dot(norm, lightDirection), 0.0f) * intensityOfLight; 

        float specularLight = 0.50f;
        vec3 viewDirection = normalize(cameraPos - currentPosition);
        vec3 reflectionDirection = reflect(-lightDirection, norm);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);

        totalspecular += specAmount * specularLight * intensityOfLight;
    }  
    
    // ZMIANA: Używamy UV zamiast texCoord, żeby połysk podążał za teksturą!
    if(useSpecularMap){
        totalspecular *= texture(specularMap, uv).r;
    }
    
    // ZMIANA: Oddzielamy światło bazowe od połysku
    vec4 baseTextureColor = texture(tex0, uv);
    vec4 ambientDiffuseColor = baseTextureColor * (diffuse + ambient) * lightColor;
    vec4 specularColor = vec4(1.0f) * totalspecular * lightColor; // Połysk jest biały/koloru światła
    
    // Dodajemy połysk na wierzch (nie mnożymy!)
    return ambientDiffuseColor + specularColor;
}

void main()
{
    //rotation of the texture
    float s = sin(texRotation);
    float c = cos(texRotation);    
    mat2 rotationMatrix = mat2(c, -s, s, c);

    vec2 centeredTexCoord = texCoord - vec2(0.5f, 0.5f);
    vec2 uv = rotationMatrix * texScale * centeredTexCoord;   
    uv = uv + vec2(0.5f, 0.5f) + texShift; 

    // Finalny kolor z nowej funkcji oświetlenia
    FragColor = calculateLighting(uv);
}