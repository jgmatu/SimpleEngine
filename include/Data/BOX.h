#ifndef __BOXFILE__
#define __BOXFILE__

#include <glad/glad.h>

//Describimos un cubo
//*******************
//Se replican vertices para que cada cara
//tenga una normal distinta.

const std::vector<GLuint> cubeTriangleIndex = {
    //Cara z = 1
    0,1,2, 3,4,5,

    //Cara z = -1
    6,7,8, 9,10,11,

    //Cara x = 1
    12,13,14, 15,16,17,

    //Cara x = -1
    18,19,20, 21,22,23,

    //Cara y = 1
    24,25,26, 27,28,29,

    //Cara y = -1
    30,31,32, 33,34,35,
};

// Posicion de los vertices
const std::vector<GLfloat> cubeVertexPos = {
    // z = -1
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

     // z = 1
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    // x = 1
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    // x = -1
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,

     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,

     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

// Normal de los vertices
const std::vector<GLfloat> cubeVertexNormal = {
    // z = -1
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,

    // z = 1
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,

    // x = -1
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,

    // x = 1
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    // y = -1
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,

    // y = 1
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f
};

//Cood. de textura de los vertices
const std::vector<GLfloat> cubeVertexTexCoord = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,

    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,

    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
 };


const GLfloat cubeVertexTangent[] = {
    // Cara z = 1
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,

    // Cara z = -1
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,

    // Cara x = 1
    0.0f,	0.0f,	-1.0f,
    0.0f,	0.0f,	-1.0f,
    0.0f,	0.0f,	-1.0f,
    0.0f,	0.0f,	-1.0f,

    // Cara x = -1
    0.0f,	0.0f,	1.0f,
    0.0f,	0.0f,	1.0f,
    0.0f,	0.0f,	1.0f,
    0.0f,	0.0f,	1.0f,

    // Cara y = 1
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,

    // Cara y = -1
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
    1.0f,	0.0f,	0.0f,
};

#endif
