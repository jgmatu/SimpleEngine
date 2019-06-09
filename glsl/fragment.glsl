#version 330 core

struct Material {
    vec3 ambient;

    sampler2D texture_diffuse0;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;

    sampler2D texture_specular0;
    sampler2D texture_specular1;

    float shininess;
};

struct Directional {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};

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

#define NR_POINT_LIGHTS 1

uniform Material material;

uniform Directional directional;
uniform Point points[NR_POINT_LIGHTS];
uniform Spot spot;

// Viewer position...
uniform vec3 viewPos;

// Parametros del programa   de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

// Final fragment...
out vec4 fragColor;

vec3 calcPointLight(Point light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcDirLight(Directional light, vec3 normal, vec3 viewDir);
vec3 calcSpotLight(Spot spot, vec3 norm, vec3 fragPos, vec3 viewDir);
float linearizeDepth(float depth);

uniform sampler2D screenTexture;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // phase 1: Directional lights
//    vec3 result = calcDirLight(directional, norm, viewDir);

    // phase 2: Point lights
    vec3 result = vec3(0, 0, 0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calcPointLight(points[i], norm, fragPos, viewDir);
    }
    // phase 3: Spot light
//    result += calcSpotLight(spot, norm, fragPos, viewDir);

    fragColor = vec4(result, 1.0);

//    vec4 diffuse  = vec4(texture(material.texture_diffuse0, texCoord));
//    vec4 specular = vec4(texture(material.texture_specular0 , texCoord));

//    fragColor = mix(diffuse, specular, 0.5);
}


vec3 calcDirLight(Directional directional, vec3 normal, vec3 viewDir)
{
    // Directional...
    vec3 lightDir = normalize(-directional.direction);

    // Diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading...
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024.0);

//    vec3 ambient  = light.ambient * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 diffuse  = directional.diffuse * diff * vec3(texture(material.texture_diffuse0, texCoord));
//    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, texCoord));

//    return ambient + diffuse + specular;
//    return ambient + diffuse;
    return diffuse;
}

vec3 calcPointLight(Point point, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(point.position - fragPos);

    // diffuse shading...
    float diff = max(dot(normal, lightDir), 0.1);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 2.0);

    // attenuation
    float distance = length(point.position - fragPos);
    float attenuation = 1.0 / (point.constant + point.linear * distance + point.quadratic * (distance * distance));

    // combine results
    vec3 diffuse  = point.diffuse * diff * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 specular = point.specular * spec * vec3(texture(material.texture_specular0 , texCoord));

    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    return diffuse + specular;
}

vec3 calcSpotLight(Spot spot, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(spot.position - fragPos);

    // Spot focus with intensity value defined...
    float theta = dot(lightDir, normalize(-spot.direction));
    float epsilon = spot.cutOff - spot.outerCutOff;
    float intensity = clamp((theta - spot.outerCutOff) / epsilon, 0.0, 1.0);

    // diffuse shading..
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Combine results...
    vec3 ambient  = spot.ambient * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 diffuse  = spot.diffuse  * diff * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 specular = spot.specular * spec * vec3(texture(material.texture_specular0, texCoord));

    ambient = ambient * intensity;
    diffuse = diffuse * intensity;
    specular = specular * intensity;

    // Attenuation...
    float distance = length(spot.position - fragPos);
    float attenuation = 1.0 / (spot.constant + spot.linear * distance + spot.quadratic * (distance * distance));

    ambient = ambient * attenuation;
    diffuse = ambient * attenuation;
    specular = ambient * attenuation;

    return ambient + diffuse + specular;
}

float linearizeDepth(float depth)
{
    float near = 0.1;
    float far  = 100.0;

    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}
