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

#define NR_POINT_LIGHTS 4

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
    vec3 result = calcDirLight(directional, norm, viewDir);

    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calcPointLight(points[i], norm, fragPos, viewDir);
    }
    // phase 3: Spot light
    result += calcSpotLight(spot, norm, fragPos, viewDir);

//    float depth = linearizeDepth(gl_FragCoord.z);
//    fragColor = vec4(result, 1.0);

    vec4 textColor = texture(material.texture_diffuse0, texCoord);
    if (textColor.a < 0.01) {
        discard;
    }
    fragColor = textColor;
}


vec3 calcDirLight(Directional light, vec3 normal, vec3 viewDir)
{
    // Directional...
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading...
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, texCoord));

    return diffuse + specular;
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
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, texCoord));

    diffuse = ambient * attenuation;
    specular = ambient * attenuation;

    return ambient + diffuse + specular;
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
    vec3 diffuse  = spot.diffuse  * diff * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 specular = spot.specular * spec * vec3(texture(material.texture_specular0, texCoord));

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
