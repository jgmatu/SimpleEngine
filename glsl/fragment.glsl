#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Directional {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};
uniform Directional directional;

struct Point {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attenuation factor...
    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform Point pointLights[NR_POINT_LIGHTS];

struct Spot {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attenuation factor...
    float constant;
    float linear;
    float quadratic;
};
uniform Spot spot;

// Viewer position...
uniform vec3 viewPos;

// Parametros del programa de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

// Final fragment...
out vec4 fragColor;

vec3 calcPointLight(Point light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcDirLight(Directional light, vec3 normal, vec3 viewDir);
/*
void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = calcDirLight(directional, norm, viewDir);

    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calcPointLight(pointLights[i], norm, fragPos, viewDir);
    }

    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    fragColor = vec4(result, 1.0);
}
*/

void main()
{
    vec3 lightDir = normalize(spot.position - fragPos);

    // Ambient...
    vec3 ambient = spot.ambient * vec3(texture(material.diffuse, texCoord)).rgb;

    // Diffuse...
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spot.diffuse * diff * vec3(texture(material.diffuse, texCoord)).rgb;

    // Specular...
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128.0);
    vec3 specular = spot.specular * spec * vec3(texture(material.specular, texCoord)).rgb;

    // Attenuation factor...
    float distance = length(spot.position - fragPos);
    float attenuation = 1.0 / (spot.constant + spot.linear * distance + spot.quadratic * (distance * distance));

    ambient = ambient * attenuation;
    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    // Spot focus with intensity value defined...
    float theta = dot(lightDir, normalize(-spot.direction));
    float epsilon = spot.cutOff - spot.outerCutOff;
    float intensity = clamp((theta - spot.outerCutOff) / epsilon, 0.0, 1.0);

    ambient = ambient * intensity;
    diffuse = diffuse * intensity;
    specular = specular * intensity;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}

vec3 calcDirLight(Directional light, vec3 normal, vec3 viewDir)
{
    // Directional...
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    return ambient + diffuse + specular;
}

vec3 calcPointLight(Point light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient  = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return ambient + diffuse + specular;
}
