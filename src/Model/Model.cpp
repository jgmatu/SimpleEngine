#include "Model/Model.hpp"

Model::Model() :
    _meshes(),
    _textures_loaded(),
    _directory()
{
    ;
}

Model::Model(std::string path) :
    Model::Model()
{
    loadModel(path);
}

Model::~Model()
{
    for (unsigned i = 0; i < _meshes.size(); ++i) {
        delete _meshes[i];
    }
    _meshes.clear();
}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // Process all the node's meshes (if any)
    for (unsigned i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->addMesh(processMesh(mesh, scene));
    }
    // Then do the same for each of its children
    for (unsigned i = 0; i < node->mNumChildren; ++i) {
        this->processNode(node->mChildren[i], scene);
    }
}

void Model::addMesh(Mesh *mesh) {
    _meshes.push_back(mesh);
}

Mesh* Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<__Texture__> textures;

    for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0])  {
            // does the mesh contain texture coordinates?
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        // process vertex positions, normals and texture coordinates
        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for(unsigned j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<__Texture__> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<__Texture__> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return new Mesh(vertices, indices, textures);
    }

std::vector<__Texture__> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<__Texture__> textures;

    for (unsigned i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned j = 0; j < _textures_loaded.size() && !skip; j++) {
            if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(_textures_loaded[j]);
                skip = true;
            }
        }
        if (!skip) {   // if texture hasn't been loaded already, load it
            __Texture__ texture;
            texture.path = _directory + "/";
            texture.type = typeName;
            texture.filename = str.C_Str();
            textures.push_back(texture);
            _textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

void Model::active() {
    for (unsigned i = 0; i < _meshes.size(); ++i) {
        _meshes[i]->loadTextures();
        _meshes[i]->active();
    }
}

void Model::render(Program *program) {
    for (unsigned i = 0; i < _meshes.size(); ++i) {
        _meshes[i]->draw(program);
    }
}

std::ostream& operator<<(std::ostream& os, const Model& model) {
    for (unsigned i = 0; i < model._meshes.size(); ++i) {
        os << *model._meshes[i];
    }
    return os;
}
