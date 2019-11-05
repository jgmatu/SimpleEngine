#version 330 core

struct Material {
    int isrgb;
    vec3 rgb;

    sampler2D texture_diffuse0;
    sampler2D texture_diffuse1;

    sampler2D texture_specular0;
    sampler2D texture_specular1;

    sampler2D texture_normal0;
    sampler2D texture_normal1;

    float shininess;
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

#define MAX_POINT_LIGHTS 255

uniform Material material;

uniform int npoints;
uniform Point points[MAX_POINT_LIGHTS];
uniform Spot spot;

uniform Directional directional;

// Viewer position...
uniform vec3 viewPos;

// Parametros del programa   de vertices del modelo...

in VS_OUT {
    vec2 textCoord;
    vec3 TangentPointPos[MAX_POINT_LIGHTS];
    vec3 TangentSpotPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    mat3 TBN;
    // Materials with no one normal map
    vec3 normal;
} fs_in;


// Final fragment...
out vec4 fragColor;

vec4 calcPointLight(Point light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 calcDirLight(Directional light, vec3 normal, vec3 viewDir);
vec4 calcSpotLight(Spot spot, vec3 norm, vec3 fragPos, vec3 viewDir);
float linearizeDepth(float depth);

uniform sampler2D screenTexture;

void main()
{
    vec3 norm = texture(material.texture_normal0, fs_in.textCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);
    norm = normalize(fs_in.TBN * norm);

//    norm = normalize(fs_in.normal);

    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    // phase 1: Directional lights
    result += calcDirLight(directional, norm, viewDir);

    // phase 2: Point lights
//    for (int i = 0; i < npoints; ++i) {
//        result += calcPointLight(points[i], norm, fs_in.TangentFragPos, viewDir);
//    }

    // phase 3: Spot light ...
//    result += calcSpotLight(spot, norm, fs_in.TangentFragPos, viewDir);

    fragColor = result;
}

vec4 calcDirLight(Directional directional, vec3 normal, vec3 viewDir)
{
    // Directional...
    vec3 lightDir = normalize(-directional.direction);

    // Diffuse shading...
    float diff = max(dot(normal, lightDir), 0.1);

    // Specular shading...
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024.0);

    vec4 diffuse = directional.diffuse * diff * texture(material.texture_diffuse0, fs_in.textCoord);
    vec4 specular = directional.specular * spec * texture(material.texture_specular0, fs_in.textCoord);

    return diffuse + specular;
}

vec4 calcPointLight(Point point, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(point.position - fragPos);

    // diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 128.0);

    // attenuation
    float distance = length(point.position - fragPos);
    float attenuation = 1.0 / (point.constant + point.linear * distance + point.quadratic * (distance * distance));

    // combine results
    vec4 diffuse = point.diffuse * diff * texture(material.texture_diffuse0, fs_in.textCoord);
    vec4 specular = point.specular * spec * texture(material.texture_specular0 , fs_in.textCoord);

    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    return diffuse + specular;
}

vec4 calcSpotLight(Spot spot, vec3 normal, vec3 fragPos, vec3 viewDir)
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
    vec4 diffuse = spot.diffuse  * diff * texture(material.texture_diffuse0, fs_in.textCoord);
    vec4 specular = spot.specular * spec * texture(material.texture_specular0, fs_in.textCoord);

    diffuse = diffuse * intensity;
    specular = specular * intensity;

    // Attenuation...
    float distance = length(spot.position - fragPos);
    float attenuation = 1.0 / (spot.constant + spot.linear * distance + spot.quadratic * (distance * distance));

    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    return diffuse + specular;
}

float linearizeDepth(float depth)
{
    float near = 0.1;
    float far  = 100.0;

    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}
