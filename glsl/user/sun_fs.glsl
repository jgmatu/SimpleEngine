
// Parametros del programa   de vertices del modelo...
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;
in mat3 TBN;

void main()
{
    vec3 _normal = texture(material.texture_normal0, texCoord).rgb;
    _normal = normalize(normal * 2.0 - 1.0);
    vec3 norm = normalize(_normal);
    norm = normalize(-normal);  // When we scale the object the normals will changed :) normalize again! :D

    vec3 viewDir = normalize(viewPos - fragPos);
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    // phase 1: Directional lights
    //  result = calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);
 
    // phase 2: Point lights
    if (npoints == 1) {
        result = calcPointLight(points[0], material.texture_diffuse0, material.texture_specular0, texCoord, norm, fragPos, viewDir);
    }
    fragColor = result;
}
