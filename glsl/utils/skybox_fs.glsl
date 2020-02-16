uniform samplerCube skybox;

in vec3 texCoords;

void main()
{
    fragColor = texture(skybox, texCoords);
}
