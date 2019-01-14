
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

void ObjectFactory::generateDemoObjects()
{
    Program *program = new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl");

    std::vector<glm::vec3> point_positions = {
        glm::vec3( 2.0,  2.0, -1.0),
        glm::vec3(-2.0,  1.0,  1.0),
        glm::vec3(-1.0,  2.0,  3.0),
        glm::vec3( 0.0, -2.0,  0.0)
    };

    std::vector<glm::vec3> cube_positions = {
        glm::vec3(2.0,  2.0, -2.0),
        glm::vec3(-2.0, 1.0, 0.0),
        glm::vec3(-1.0,  2.0, 2.0),
        glm::vec3(0.0, -2.0, -1.0),
        glm::vec3(1.0, 1.0, -1.0)
    };

    std::vector<Light*> points;
    for (unsigned i = 0; i < point_positions.size(); ++i) {
        points.push_back(new Point(i, point_positions[i]));
    }
    glm::vec3 direction = glm::vec3(0.0, -1.0, 0.0);

    Model *cube_mesh = new Model();
    cube_mesh->addMesh(getCubeMesh());
//    for (unsigned i = 0; i < 1; ++i) {
//        GameObject *cube = new GameObject(i, "*** CUBE ***");

//        Material *cube_material = new Material(cube_mesh);
//        cube_material->setProgram(program);

//        cube_material->setLigth(new Specular(glm::vec3(0.5f, 0.5f, 0.5f), 0.5));
//        cube_material->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
//        cube_material->setLigth(new Directional(direction));
//        for (unsigned j = 0; j < points.size(); ++j) {
//            cube_material->setLigth(points[j]);
//        }
//        cube->addComponent(cube_material);
//        _GameObjects.push_back(cube);
//    }

//    Material *lamp_mat = new Material(cube_mesh);

//    lamp_mat->setProgram(program);
//    lamp_mat->setColor(glm::vec3(1.0, 1.0, 1.0));

//    lamp_mat->setLigth(new Ambient(glm::vec3(5.05, 5.05, 5.05)));
//    lamp_mat->setLigth(new Diffuse(glm::vec3(0.5, 0.5, 0.5)));

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

    nanosuit->setLigth(new Specular(glm::vec3(0.7, 0.7, 0.7), 0.078125));
    for (unsigned i = 0; i < points.size(); ++i) {
        nanosuit->setLigth(points[i]);
    }
    nanosuit->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
    nanosuit->setLigth(new Directional(direction));

    GameObject *nanosuit_go = new GameObject(30, "Complex model");
    nanosuit_go->addComponent(nanosuit);
    _GameObjects.push_back(nanosuit_go);
}

Mesh* ObjectFactory::getPlaneMesh() {
    Mesh *mesh = new Mesh();

    std::vector<GLfloat> position = {
         0.0f,  0.0f,  0.0f, // 0
         0.5f,  0.0f,  0.0f, // 1

         0.0f,  0.5f,  0.0f, // 2

        -0.5f,  0.0f,  0.0f, // 3
         0.0f, -0.5f,  0.0f, // 4
    };

    std::vector<GLuint> index = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
    };

    std::vector<GLfloat> textCoord = {
        // Cara z = 1
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        // Cara z = -1
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
    };

    std::vector<GLfloat> normal = {
        0.0f,   1.0f,   0.0f,
        0.0f,   1.0f,   0.0f,

        0.0f,   1.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
    };
    return mesh;
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

    for (unsigned i = 0, j = 0; i < cubeVertexPos.size(); i += 3, j += 2) {
        Vertex vertex;

        glm::vec3 normal;
        glm::vec3 position;
        glm::vec2 text;

        position.x = cubeVertexPos[i];
        normal.x = cubeVertexNormal[i];

        position.y = cubeVertexPos[i + 1];
        normal.y = cubeVertexNormal[i + 1];

        normal.z = cubeVertexNormal[i + 2];
        position.z = cubeVertexPos[i + 2];

        text.x = cubeVertexTexCoord[j];
        text.y = cubeVertexTexCoord[j + 1];

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
