in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;
in vec3 normal;
in vec2 texCoord;

void main()
{
    vec3 norm = texture(material.texture_normal0, texCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);

    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    // phase 1: Directional lights
    result += calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);

    fragColor = result;
}