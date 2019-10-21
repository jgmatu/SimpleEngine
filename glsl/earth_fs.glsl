#version 330 core

struct Material {
    sampler2D texture_diffuse0;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;

    sampler2D texture_specular0;
    sampler2D texture_specular1;
};

struct Directional {

    vec4 diffuse;
    vec4 specular;

    vec3 direction;
};

struct Point {
    vec3 position;

    vec4 diffuse;
    vec4 specular;

    // Attenuation factor...
    float constant;
    float linear;
    float quadratic;
};

struct Spot {
    vec3 position;
    vec3 direction;

    vec4 diffuse;
    vec4 specular;

    // Attenuation factor...
    float constant;
    float linear;
    float quadratic;

    // Spot factors...
    float cutOff;
    float outerCutOff;
};

uniform Material material;

#define MAX_POINT_LIGHTS 255

uniform int npoints;
uniform Point points[MAX_POINT_LIGHTS];
uniform Directional directional;

// Viewer position...
uniform vec3 viewPos;

// Parametros del programa   de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

// Final fragment...
out vec4 fragColor;

vec4 calcPointLight(Point point, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 calcDirLight(Directional light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    // phase 1: Directional lights
    result = calcDirLight(directional, norm, viewDir);

    // phase 2: Point lights
    for (int i = 0; i < npoints; ++i) {
        result += calcPointLight(points[i], norm, fragPos, viewDir);
    }

    fragColor = result;
}

vec4 calcDirLight(Directional directional, vec3 normal, vec3 viewDir)
{
    // Directional...
    vec3 lightDir = normalize(-directional.direction);

    // Diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading...
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.0);

    vec4 diffuse = directional.diffuse * diff * texture(material.texture_diffuse0, texCoord);
    vec4 specular = directional.specular * spec * texture(material.texture_specular0, texCoord);

    return diffuse + specular;
}

vec4 calcPointLight(Point point, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(point.position - fragPos);

    // diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.0);

    // attenuation
    float distance = length(point.position - fragPos);
    float attenuation = 1.0 / (point.constant + point.linear * distance + point.quadratic * (distance * distance));

    // combine results
    vec4 diffuse = point.diffuse * diff * texture(material.texture_diffuse0, texCoord);
    vec4 specular = point.specular * spec * texture(material.texture_specular0 , texCoord);

    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    return diffuse + specular;
}
