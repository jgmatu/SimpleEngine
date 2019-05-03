#ifndef TYPECOMP_H
#define TYPECOMP_H

// Tiempo de refresco del Engine...
// Importante para marcar las velocidades y movimientos
// de los GameObjects..

#define LOOP_INTERVAL_TIME_MS 10

const static float MOVEMENT_TIME = LOOP_INTERVAL_TIME_MS;

enum class TypeComp {
    MATERIAL, TRANSFORM, TEXTURE, CAMERA, SKYBOX
};

enum class CompLigth {
    AMBIENT, DIFFUSE, SPECULAR, SCENE, DIRECTIONAL, POINT, SPOT
};

#endif // TYPECOMP_H
