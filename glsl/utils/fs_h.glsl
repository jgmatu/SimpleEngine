#version 330 core

struct Material {
    sampler2D texture_diffuse0;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;

    sampler2D texture_specular0;
    sampler2D texture_specular1;

    sampler2D texture_normal0;
    sampler2D texture_normal1;
};

uniform Material material;
uniform vec3 viewPos;

out vec4 fragColor;
