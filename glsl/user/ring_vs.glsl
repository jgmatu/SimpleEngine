out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

void main()
{
    texCoord = aTexCoords;
    normal = mat3(transpose(inverse(model))) * aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
