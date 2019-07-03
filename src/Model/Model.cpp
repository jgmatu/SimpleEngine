#include "Model/Model.hpp"

Model::Model() :
    _meshes(),
    _directory()
{
    _material = nullptr;
}

Model::Model(Mesh *mesh) :
    Model::Model()
{
    _meshes[mesh->getId()] = mesh;
}

Model::Model(std::string path) :
    Model::Model()
{
    loadModel(path);
}

Model::~Model()
{
    std::map<std::string, Mesh*>::iterator it = _meshes.begin();

    while (it != _meshes.end()) {
        it = _meshes.erase(it);
    }
    _meshes.clear();
}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        throw;
    }
    _directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // Process all the node's meshes (if any)
    for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->addMesh(processMesh(std::to_string(i), mesh, scene));
    }
    // Then do the same for each of its children
    for (uint32_t i = 0; i < node->mNumChildren; ++i) {
        this->processNode(node->mChildren[i], scene);
    }
}

void Model::addMesh(Mesh *mesh) {
    _meshes[mesh->getId()] = mesh;
}

Mesh* Model::processMesh(std::string id_mesh, aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture*> textures;

    for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
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
    for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for(uint32_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture*> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture*> specularMaps = loadTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    // Add primitive textures for complex models...
    Mesh *mesh_engine = new Mesh(id_mesh, vertices, indices);
    for (uint32_t i = 0; i < textures.size(); ++i) {
        mesh_engine->setTexture(textures[i]);
    }
    return mesh_engine;
}

std::vector<Texture*> Model::loadTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture*> textures;
    std::vector<Texture*> _textures_loaded;

    for (uint32_t i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (uint32_t j = 0; j < _textures_loaded.size() && !skip; j++) {
            if (std::strcmp(_textures_loaded[j]->_path.data(), str.C_Str()) == 0) {
                textures.push_back(_textures_loaded[j]);
                skip = true;
        }
        if (!skip) {   // if texture hasn't been loaded already, load it
    }
            Texture *texture = new Texture(str.C_Str(), typeName);
            texture->_path = _directory + "/";
            textures.push_back(texture);
            _textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

void Model::setMaterial(Material *material)
{
    _material = material;
}

void Model::update(Material *material)
{
    _material->update(material);
}

void Model::active() {
    if (!_material) {
        std::cerr << "active: No material load on model!" << '\n';
        throw;
    }

    std::map<std::string, Mesh*>::iterator it;
    for (it = _meshes.begin(); it != _meshes.end(); ++it) {
        Mesh *mesh = it->second;

        mesh->setProgram(_material->_program);
        mesh->active();

        // Load all material textures to the proper mesh..
        std::vector<Texture*> textures = this->_material->_textures[it->first];
        for (uint32_t i = 0; i < textures.size(); ++i) {
            mesh->setTexture(textures[i]);
        }
        mesh->activeTextures();
    }
}

void Model::draw() {
    if (!_material->_uniforms) {
        std::cerr << "draw: No material loaded!" << '\n';
        throw;
    }
    std::map<std::string, Mesh*>::iterator it;

    for (it = _meshes.begin(); it != _meshes.end(); ++it) {
        Mesh *mesh = it->second;

        mesh->update(_material->_uniforms);
        mesh->draw();
    }
}

std::ostream& operator<<(std::ostream& os, const Model& model) {
    std::map<std::string, Mesh*>::const_iterator it_mesh;

    for (it_mesh = model._meshes.begin(); it_mesh != model._meshes.end(); ++it_mesh) {
        Mesh *mesh = it_mesh->second;
        os << *mesh << '\n';
    }
    return os;
}
