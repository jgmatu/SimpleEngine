#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

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
    vec3 objectColor = vec3(0.0, 0.0, 0.0);
    vec3 lightPos = vec3(0.0, 1.5, 0.0);
    vec3 viewPos = vec3(0.0, 0.0, -4.0);

    // Ambient...
    vec3 ambient = ambientStrength * ambientColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;

    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024);
    vec3 specular = specularStrength * spec * specularColor;

    objectColor = texture(diffuseTexture, texCoord).rgb + objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}
