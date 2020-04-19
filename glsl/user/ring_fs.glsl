// Parametros del programa   de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    // phase 1: Directional lights
    // result = calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);

    // phase 2: Point lights
    if (npoints > 0) {
        fragColor = calcPointLight(points[0], material.texture_diffuse0, material.texture_specular0, texCoord, norm, fragPos, viewDir) * 0.5;
    }
}