#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
#include <string>

#include "Model/Mesh.hpp"
#include "Program/Program.hpp"

class Model {

public:

    Model(std::string path);
    Model();
    ~Model();

    void active();
    void render(Program *program);
    void addMesh(Mesh *mesh);

    friend std::ostream& operator<<(std::ostream& os, const Model& model);

private:

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<__Texture__> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    std::vector<Mesh*> _meshes;
    std::vector<__Texture__> _textures_loaded;
    std::string _directory;

    friend class GameObject;
};

#endif
