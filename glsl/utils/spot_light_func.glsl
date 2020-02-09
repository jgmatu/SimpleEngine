
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

vec4 calcSpotLight(Spot s, sampler2D texture_diffuse, sampler2D texture_specular, float shininess, vec2 textCoord, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(s.position - fragPos);

    // Spot focus with intensity value defined...
    float theta = dot(lightDir, normalize(-s.direction));
    float epsilon = s.cutOff - s.outerCutOff;
    float intensity = clamp((theta - s.outerCutOff) / epsilon, 0.0, 1.0);

    // diffuse shading..
    float diff = max(dot(norm, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Combine results...
    vec4 diffuse = s.diffuse  * diff * texture(texture_diffuse, textCoord);
    vec4 specular = s.specular * spec * texture(texture_specular, textCoord);

    diffuse = diffuse * intensity;
    specular = specular * intensity;

    // Attenuation...
    float distance = length(s.position - fragPos);
    float attenuation = 1.0 / (s.constant + s.linear * distance + s.quadratic * (distance * distance));

    diffuse = diffuse * attenuation;
    specular = specular * attenuation;

    return diffuse + specular;
}

uniform Spot spot;
