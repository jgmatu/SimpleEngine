out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;
out mat3 TBN;

void main()
{
    normal = mat3(transpose(inverse(model))) * aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));
    texCoord = aTexCoords;
    TBN = getTBNMatrix(model);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
