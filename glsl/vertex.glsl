#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 viewPos;

struct Point {
    vec3 position;

    vec4 diffuse;
    vec4 specular;

    // Attenuation factor...
    float constant;
    float linear;
    float quadratic;
};


#define MAX_POINT_LIGHTS 255
uniform int npoints;
uniform Point points[MAX_POINT_LIGHTS];


out VS_OUT {
    vec2 textCoord;
    vec3 TangentPointPos[MAX_POINT_LIGHTS];
    vec3 TangentSpotPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    mat3 TBN;
    // Materials with no one normal map
    vec3 normal;
} vs_out;


mat3 getTBNMatrix(mat4 model);

void main()
{
    mat3 TBN = getTBNMatrix(model);

    vs_out.textCoord = aTexCoords;
    // phase 2: Point lights
    for (int i = 0; i < npoints; ++i) {
        vs_out.TangentPointPos[i] = transpose(TBN) * points[i].position;
    }
    vs_out.TangentViewPos = transpose(TBN) * viewPos;
    vs_out.TangentFragPos = transpose(TBN) * vec3(model * vec4(aPos, 1.0));
    vs_out.TBN = TBN;
    vs_out.normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

mat3 getTBNMatrix(mat4 model)
{
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));

    // Re-orthogonalize T with respect to N.
    T = normalize(T - dot(T, N) * N);

    // Then retrieve perpendicular vector B with the cross product of T and N.
    vec3 B = cross(N, T);

    return mat3(T, B, N);
}
