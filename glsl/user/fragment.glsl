// Parametros del programa   de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    // phase 2: Point lights
    for (int i = 0; i < npoints; ++i) {
        result += calcPointLight(points[i], material.texture_diffuse0, material.texture_specular0, texCoord, norm, fragPos, viewDir);
    }
    fragColor = result;
}