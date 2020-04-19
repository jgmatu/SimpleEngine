out vec3 texCoords;

void main()
{
    texCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0) * 100;
    gl_Position = pos.xyww;
}