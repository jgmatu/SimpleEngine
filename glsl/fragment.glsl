#version 330 core

// Parametros del programa de vertices...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

// Texturas del fragmento...
uniform sampler2D diffuseTexture;

// Ambient parameters...
uniform vec3 ambientColor;
uniform float ambientStrength;

// Specular parameters...
uniform vec3 specularColor;
uniform float specularStrength;

// Diffuse params...
uniform vec3 diffuseColor;
uniform float diffuseStrength;

out vec4 fragColor;

void main()
{
    vec3 objectColor = vec3(0.0, 0.0, 0.0); // Color del objeto...

    vec3 lightPos = vec3(0.0, 0.0, 0.0); // Posición de la luz Direccional...

    vec3 viewPos = vec3(0.0, 0.0, -4.0); // Depende de la posición de la camara...

    // Ambient...
    vec3 ambient = ambientStrength * ambientColor;

    // Diffuse...
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0) * diffuseStrength;
    vec3 diffuse = diff * diffuseColor;

    // Specular...
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024);
    vec3 specular = specularStrength * spec * specularColor;

    objectColor = texture(diffuseTexture, texCoord).rgb + objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}
