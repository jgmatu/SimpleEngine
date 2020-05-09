// Parametros del programa   de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);
    // phase 1: Directional lights
    result = calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);

    fragColor = result;
}