#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

mat3 getTBNMatrix(mat4 model);

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    texCoord = aTexCoords;
    fragPos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;

    mat3 TBN = getTBNMatrix(model);
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * fragPos;
}

mat3 getTBNMatrix(mat4 model)
{
    vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));

    // Re-orthogonalize T with respect to N.
    T = normalize(T - dot(T, N) * N);

    // Then retrieve perpendicular vector B with the cross product of T and N.
    vec3 B = cross(N, T);

    return transpose(mat3(T, B, N));
}
