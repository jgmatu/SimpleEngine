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

vec3 calcPointLight(Point point, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0); // Es una variable unform que va reflejado en la tierra y en la luna como el color del sol.
    vec3 lightPos = vec3(0.0, 0.0, 0.0); // 0 0 0 La luz solar

    vec3 viewDir = normalize(fragPos - viewPos);

    float ambientStrength = 1.2;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse...
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);


    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Result fragments...
    vec3 result = (ambient + diffuse) * texture(material.texture_diffuse0, texCoord).rgb;

    result = calcPointLight(points[0], norm, fragPos, viewDir);
    fragColor = vec4(result, 1.0);
}

vec3 calcPointLight(Point point, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(fragPos - point.position);

    // diffuse shading...
    float diff = max(dot(normal, lightDir), 1.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024.0);

    // attenuation
    float distance = length(point.position - fragPos);
    float attenuation = 1.0 / (point.constant + point.linear * distance + point.quadratic * (distance * distance));

    // combine results
//    vec3 ambient  = point.ambient * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 diffuse  = point.diffuse * diff * vec3(texture(material.texture_diffuse0, texCoord));
    vec3 specular = point.specular * spec; // * vec3(texture(material.texture_specular0, texCoord));

//    ambient = ambient * attenuation;
    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

//    return ambient + diffuse + specular;
    return diffuse + specular;
}
