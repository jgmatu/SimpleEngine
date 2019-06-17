#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include "Model/Mesh.hpp"
#include "Program/Program.hpp"

class Model {

public:

    Model(std::string path);
    Model(Mesh *mesh);

    Model();
    ~Model();

    void active();
    void draw();
    void addMesh(Mesh *mesh);

    void setProgram(Program *program);
    void setUniforms(Uniforms *uniforms);
    void setTextures(std::map<std::string, std::vector<Texture*>> textures);

    friend std::ostream& operator<<(std::ostream& os, const Model& model);

private:

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh* processMesh(std::string id_mesh, aiMesh *mesh, const aiScene *scene);

    std::vector<Texture*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    std::map<std::string, Mesh*> _meshes;
    // Textures loaded from simple geometries...
    // this textures are mapped with id_texture...
    std::map<std::string, std::vector<Texture*>> _textures;

    std::vector<Texture*> _textures_loaded;

    std::string _directory;

    Program *_program;
    Uniforms *_uniforms;
};

#endif
