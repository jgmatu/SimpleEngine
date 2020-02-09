
struct Point {
    vec3 position;

    vec4 diffuse;
    vec4 specular;

    // Attenuation factor...
    float constant;
    float linear;
    float quadratic;
};

vec4 calcPointLight(Point p, sampler2D texture_diffuse, sampler2D texture_specular, vec2 textCoord, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(p.position - fragPos);

    // diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 128.0);

    // attenuation
    float distance = length(p.position - fragPos);
    float attenuation = 1.0 / (p.constant + p.linear * distance + p.quadratic * (distance * distance));

    // combine results
    vec4 diffuse = p.diffuse * diff * texture(texture_diffuse, textCoord);
    vec4 specular = p.specular * spec * texture(texture_specular , textCoord);

    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    return diffuse + specular;
}

#define MAX_POINT_LIGHTS 255
uniform int npoints;
uniform Point points[MAX_POINT_LIGHTS];
