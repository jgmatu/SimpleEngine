#include "GameObjects/ObjectFactory.hpp"

#include "Data/BOX.h"

ObjectFactory::ObjectFactory() :
    _GameObjects()
{
    std::cout << "Creating Factory Objects..." << '\n';
}

ObjectFactory::~ObjectFactory()
{
    std::cout << "Delete All Game Objects!" << '\n';

    for (unsigned i = 0; i < _GameObjects.size(); ++i) {
        delete _GameObjects[i];
    }
}

void ObjectFactory::addGameObject(GameObject *gameObject)
{
    _GameObjects.push_back(gameObject);
};

GameObject* ObjectFactory::getGameObject(unsigned id)
{
    return _GameObjects[id];
}

std::vector<Light*> getLigthPoints()
{
    std::vector<glm::vec3> point_positions = {
        glm::vec3( 2.0,  2.0, -1.0),
        glm::vec3(-2.0,  1.0,  1.0),
        glm::vec3(-1.0,  2.0,  3.0),
        glm::vec3( 0.0, -2.0,  0.0)
    };

    std::vector<Light*> points;
    for (unsigned i = 0; i < point_positions.size(); ++i) {
        points.push_back(new Point(i, point_positions[i]));
    }
    return points;
}

void ObjectFactory::addSceneLigths(Material *material)
{
    std::vector<Light*> points = getLigthPoints();

    for (unsigned i = 0; i < points.size(); ++i) {
        material->setLigth(points[i]);
    }
    material->setLigth(new Specular(glm::vec3(0.7, 0.7, 0.7), 0.078125));
    material->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
    material->setLigth(new Directional(glm::vec3(0.0, -1.0, 0.0)));
}

void ObjectFactory::generateDemoObjects()
{
    Program *program = new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl");

    std::vector<glm::vec3> cube_positions = {
        glm::vec3(2.0,  2.0, -2.0),
        glm::vec3(-2.0, 1.0, 0.0),
        glm::vec3(-1.0,  2.0, 2.0),
        glm::vec3(0.0, -2.0, -1.0),
        glm::vec3(1.0, 1.0, -1.0)
    };

    for (unsigned i = 0; i < 2; ++i) {
        Material *cube_material = new Material(new Model(getCubeMesh()));
        cube_material->setProgram(program);
        this->addSceneLigths(cube_material);

        GameObject *cube = new GameObject(i + 1, "*** CUBE ***");
        cube->addComponent(cube_material);

        _GameObjects.push_back(cube);
    }

//    Material *lamp_mat = new Material(cube_mesh);

//    lamp_mat->setProgram(program);

//    lamp_mat->setLigth(new Specular(glm::vec3(0.7, 0.7, 0.7), 0.078125));
//    for (unsigned i = 0; i < points.size(); ++i) {
//        lamp_mat->setLigth(points[i]);
//    }
//    lamp_mat->setLigth(new Directional(direction));

//    for (unsigned i = 0; i < points.size(); ++i) {
//        GameObject *lamp = new GameObject(9 + i, "*** LAMP *** ");
//        lamp->addComponent(lamp_mat);

//        _GameObjects.push_back(lamp);
//    }

    Material *nanosuit = new Material(new Model("../models/nanosuit/nanosuit.obj"));
    nanosuit->setProgram(program);
    this->addSceneLigths(nanosuit);

    GameObject *nanosuit_go = new GameObject(30, "Complex model");
    nanosuit_go->addComponent(nanosuit);
//    _GameObjects.push_back(nanosuit_go);

    Material *_floor = new Material(new Model(getPlaneMesh()));
    _floor->setProgram(program);
    this->addSceneLigths(_floor);

    GameObject *_floor_go = new GameObject(0, "Floor model...");
    _floor_go->addComponent(_floor);

    _GameObjects.push_back(_floor_go);

    for (unsigned i = 0; i < 5; ++i) {
        Material *grass = new Material(new Model(getPlantMesh()));
        grass->setProgram(program);
        grass->setTransparent();
        this->addSceneLigths(grass);

        GameObject *grass_go = new GameObject(111 + i, "Grass");
        grass_go->addComponent(grass);
        _GameObjects.push_back(grass_go);
    }
}

Mesh* ObjectFactory::getPlantMesh() {
    std::vector<GLfloat> positions = {
        0.0f,  0.5f,  0.0f,
        0.0f, -0.5f,  0.0f,
        1.0f, -0.5f,  0.0f,

        0.0f,  0.5f,  0.0f,
        1.0f, -0.5f,  0.0f,
        1.0f,  0.5f,  0.0f,
    };

    std::vector<unsigned> inidices = {
        0, 1, 2,
        2, 3, 4,
        4, 5, 0
    };

    std::vector<GLfloat> textCoords = {
        0.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  1.0f,
        1.0f,  0.0f
    };

    std::vector<Vertex> vertices;
    for (unsigned i = 0, j = 0; i < positions.size(); i += 3, j += 2) {
        Vertex vertex;

        vertex.Position = glm::vec3(positions[i], positions[i + 1], positions[i + 2]);
        vertex.Normal = glm::vec3(1.0f, 0.0f, 0.0f);
        vertex.TexCoords = glm::vec2(textCoords[j], textCoords[j + 1]);

        vertices.push_back(vertex);
    }

    std::vector<__Texture__> textures;
    __Texture__ texture;
    texture.path = "../resources/";
//    texture.filename = "grass.png";
    texture.filename = "blending_transparent_window.png";
    textures.push_back(texture);

    return new Mesh(vertices, inidices, textures);
}

void ObjectFactory::addSkyBox(std::string directory)
{
    ;
}

Mesh* ObjectFactory::getPlaneMesh() {
    std::vector<GLfloat> position = {
         5.0f, -0.5f,  5.0f, // 0
        -5.0f, -0.5f,  5.0f, // 1
        -5.0f, -0.5f, -5.0f, // 2

         5.0f, -0.5f,  5.0f, // 3
        -5.0f, -0.5f, -5.0f, // 4
         5.0f, -0.5f, -5.0f  // 5
    };
    std::vector<GLuint> indices = {
        1, 2, 0,
        4, 2, 3,
        5, 4, 3,
        2, 5, 1
    };
    std::vector<GLfloat> textCoord = {
        2.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 2.0f,

        2.0f, 0.0f,
        0.0f, 2.0f,
        2.0f, 2.0f
    };
    std::vector<GLfloat> normal = {
        0.0f,   1.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
        0.0f,   1.0f,   0.0f
    };

    std::vector<Vertex> vertices;
    for (unsigned i = 0, j = 0; i < position.size(); i += 3, j += 2) {
        Vertex vertex;

        vertex.Position = glm::vec3(position[i], position[i + 1], position[i + 2]);
        vertex.Normal = glm::vec3(normal[i], normal[i + 1], normal[i + 2]);
        vertex.TexCoords = glm::vec2(textCoord[j], textCoord[j + 1]);
        vertices.push_back(vertex);
    }
    std::vector<__Texture__> textures;

    __Texture__ texture;
    texture.path = "../resources/";
    texture.filename = "marble.png";
    textures.push_back(texture);

    return new Mesh(vertices, indices, textures);
}


Mesh* ObjectFactory::getCubeMesh() {
    std::vector<__Texture__> textures;
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices = cubeTriangleIndex;

    __Texture__ texture;

    texture.type = "texture_diffuse";
    texture.path = "../resources/";
    texture.filename = "container2.png";
    textures.push_back(texture);

    texture.type = "texture_specular";
    texture.path = "../resources/";
    texture.filename = "container2_specular.png";
    textures.push_back(texture);

    for (unsigned i = 0; i < __cubeVertices.size(); i += 5) {
        Vertex vertex;

        glm::vec3 normal;
        glm::vec3 position;
        glm::vec2 text;

        position.x = __cubeVertices[i];
        position.y = __cubeVertices[i + 1];
        position.z = __cubeVertices[i + 2];
        text.x = __cubeVertices[i + 3];
        text.y = __cubeVertices[i + 4];

        normal.x = cubeVertexNormal[i];
        normal.y = cubeVertexNormal[i + 1];
        normal.z = cubeVertexNormal[i + 2];

        vertex.Normal = normal;
        vertex.Position = position;
        vertex.TexCoords = text;
        vertices.push_back(vertex);
    }
    return new Mesh(vertices, indices, textures);
}

Mesh* ObjectFactory::getSphereMesh() {
    int idx = 0;

    /* Statement Exercise ... */
    std::vector<std::vector<int>> grid;

    // Buffers
    std::vector<GLfloat> posVertex;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<GLuint> indices;

    float heightSegments = 25.0f;
    float height = 25.0f;
    float width = 25.0f;
    float radius = 1.0f;
    glm::vec3 vertex(1.0f); // Row vec3...
    std::vector<Vertex> vertices;

    // Generate vertices, normals and texCoords
    for (int iy = 0; iy <= height; ++iy) {
          std::vector<int> verticesRow;
          float v = iy / heightSegments;

          for (int ix = 0; ix <= width; ++ix) {
                float u = ix / width;

                // Vertex. X.
                vertex.x = -radius * cos( u * M_PI * 2.0f ) * sin( v * M_PI );

                // Vertex. Y.
                vertex.y = radius * cos( v * M_PI );

                // Vertex. Z.
                vertex.z = radius * sin( u * M_PI * 2.0f ) * sin( v * M_PI );

                GLfloat aux[] = {vertex.x, vertex.y, vertex.z};
                posVertex.insert(posVertex.end(), aux, aux + 3);

                // Normal.
                glm::vec3 normal(vertex);
                normal = glm::normalize(normal); // Normalize... Here!

                GLfloat norm[] = {normal.x, normal.y, normal.z};
                normals.insert(normals.end(), norm, norm + 3);

                // TexCoord. Is good because draw the first texture...
                double texCoord[] = {u, 1.0 - v};
                texCoords.insert(texCoords.begin(), texCoord, texCoord + 2);
                verticesRow.push_back( idx++ );
                Vertex vertex;

                vertex.Position = glm::vec3(aux[0], aux[1], aux[2]);
                vertex.Normal = normal;
                vertex.TexCoords = glm::vec2(texCoord[0], texCoord[1]);
                vertices.push_back(vertex);
          }
          grid.push_back(verticesRow);
    }

    // Generate índices
    // Sorting of indices... (for triangles-strip)
    for (int iy = 0; iy < height; ++iy ) {
          for (int ix = 0; ix < width; ++ix ) {
                int a = grid[ iy ][ ix + 1 ];
                int b = grid[ iy ][ ix ];
                int c = grid[ iy + 1 ][ ix ];
                int d = grid[ iy + 1 ][ ix + 1 ];

                int aux[] = {a, b, d};
                indices.insert(indices.end(), aux, aux + 3);

                int bla[] = {b, c, d};
                indices.insert(indices.end(), bla, bla + 3);
          }
    }
    std::vector<__Texture__> textures;
    return new Mesh(vertices, indices, textures);
}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
