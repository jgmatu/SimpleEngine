uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

void main()
{
    texCoord = aTexCoords;
    fragPos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;

    mat3 TBN = getTBNMatrix(model);
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * fragPos;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}