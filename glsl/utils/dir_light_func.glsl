struct Directional {
    vec4 diffuse;
    vec4 specular;
    vec3 direction;
};

vec4 calcDirLight(Directional d, sampler2D texture_diffuse, sampler2D texture_specular, vec2 _textCoord, vec3 normal, vec3 viewDir)
{
    // Directional...
    vec3 lightDir = normalize(-d.direction);

    // Diffuse shading...
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading...
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1024.0);

    vec4 diffuse  = d.diffuse * diff * texture(texture_diffuse, _textCoord);
    vec4 specular = d.specular * spec * texture(texture_specular, _textCoord);

    return diffuse + specular;
}

uniform Directional directional;