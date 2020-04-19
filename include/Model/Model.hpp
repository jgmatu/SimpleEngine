#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"

class Model {

public:

    Model(std::string path);
    Model(Mesh *mesh);

    Model();
    ~Model();

    void active();
    void update(Uniforms *uniforms);
    void draw();

    void addMesh(Mesh *mesh);
    bool isTransparentModel();
    void setTransparentModel();
    bool isModelLoaded(); 
    friend std::ostream& operator<<(std::ostream& os, const Model& model);

private:

    bool isLoadModel();
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh* processMesh(std::string id_mesh, aiMesh *mesh, const aiScene *scene);
    std::vector<Texture*> loadTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    std::map<std::string, Mesh*> _meshes;
    std::string _directory;
    std::string _path;
    int _id_mesh;
    bool _isTransparentModel;
};

#endif
