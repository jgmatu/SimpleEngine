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
    // result = calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);

    // phase 2: Point lights
    if (npoints > 0) {
        result = calcPointLight(points[0], material.texture_diffuse0, material.texture_specular0, texCoord, norm, fragPos, viewDir);
    }

    vec4 textColor = texture(material.texture_diffuse0, texCoord);
    if (textColor.a < 0.1) {
        discard;
    }
    fragColor = result;
}