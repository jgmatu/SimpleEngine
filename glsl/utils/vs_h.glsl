#version 330 core
// AUTO CODE GENERTED HEADER OF VERTEX PROGRAM

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Mandatory line in your main function
// gl_Position = projection * view * model * vec4(aPos, 1.0);
