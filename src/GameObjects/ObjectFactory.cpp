
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
    Model *cube_mesh = new Model();

    std::vector<glm::vec3> positions = {
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
    for (unsigned i = 0; i < positions.size(); ++i) {
        points.push_back(new Point(i, positions[i]));
    }
    glm::vec3 direction = glm::vec3(0.0, -1.0, 0.0);

    cube_mesh->addMesh(getCubeMesh());
    for (unsigned i = 0; i < 5; ++i) {
        GameObject *cube = new GameObject(i, "*** CUBE ***");

        Material *cube_material_1 = new Material(cube_mesh);

        cube_material_1->setProgram(program);

        cube_material_1->setLigth(new Ambient(glm::vec3(0.2125, 0.1275, 0.054)));
        cube_material_1->setLigth(new Diffuse(glm::vec3(0.714, 0.4284, 0.18144)));
        cube_material_1->setLigth(new Specular(glm::vec3(0.5f, 0.5f, 0.5f), 0.5));
        cube_material_1->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
        cube_material_1->setLigth(new Directional(direction));
        for (unsigned j = 0; j < points.size(); ++j) {
            cube_material_1->setLigth(points[j]);
        }

        Material *cube_material_2 = new Material(cube_mesh);

        cube_material_2->setProgram(program);

        cube_material_2->setLigth(new Ambient(glm::vec3(0.24725, 0.1995, 0.0745)));
        cube_material_2->setLigth(new Diffuse(glm::vec3(0.75164, 0.60648, 0.22648)));
        cube_material_2->setLigth(new Specular(glm::vec3(0.5f, 0.5f, 0.5f), 0.5));
        cube_material_2->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
        cube_material_2->setLigth(new Directional(direction));
        for (unsigned j = 0; j < points.size(); ++j) {
            cube_material_2->setLigth(points[j]);
        }
        if (i % 2 == 0) {
            cube->addComponent(cube_material_1);
        } else {
            cube->addComponent(cube_material_2);
        }
        _GameObjects.push_back(cube);
    }

    Material *lamp_mat = new Material(cube_mesh);

    lamp_mat->setProgram(program);
    lamp_mat->setColor(glm::vec3(1.0, 1.0, 1.0));
    lamp_mat->setLigth(new Ambient(glm::vec3(5.05, 5.05, 5.05)));
    lamp_mat->setLigth(new Diffuse(glm::vec3(0.5, 0.5, 0.5)));
    lamp_mat->setLigth(new Specular(glm::vec3(0.7, 0.7, 0.7), 0.078125));
    for (unsigned i = 0; i < points.size(); ++i) {
        lamp_mat->setLigth(points[i]);
    }
    lamp_mat->setLigth(new Directional(direction));

    for (unsigned i = 0; i < points.size(); ++i) {
        GameObject *lamp = new GameObject(9 + i, "*** LAMP *** ");
        lamp->addComponent(lamp_mat);
        _GameObjects.push_back(lamp);
    }
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

    mesh->_vertexPos = position;
    mesh->_vertexNormal = normal;
    mesh->_vertexTexCoord = textCoord;
    mesh->_index = index;
    return mesh;
}


Mesh* ObjectFactory::getCubeMesh() {
    std::vector<__Texture__> textures;
    std::vector<Vertex> vertices;

    __Texture__ texture;

    texture.type = "texture_diffuse";
    texture.path = "../resources/";
    texture.filename = "container2.png";
    textures.push_back(texture);

    texture.type = "texture_specular";
    texture.path = "../resources/";
    texture.filename = "container2_specular.png";
    textures.push_back(texture);

    for (unsigned i = 0; i < cubeVertexPos.size(); i += 3) {
        Vertex vertex;

        for (unsigned j = 0; j < 3; ++j) {
            glm::vec3 normal;
            glm::vec3 position;
            glm::vec2 text;
            if (j == 0) {
                std::cout << "X" << '\n';
                normal.x = cubeVertexNormal[i + j];
                position.x = cubeVertexPos[i + j];
                text.x = cubeVertexTexCoord[i + j];
            }
            if (j == 1) {
                std::cout << "Y" << '\n';
                normal.y = cubeVertexNormal[i + j];
                position.y = cubeVertexPos[i + j];
                text.y = cubeVertexTexCoord[i + j];
            }
            if (j == 2) {
                std::cout << "Z" << '\n';
                normal.z = cubeVertexNormal[i + j];
                position.z = cubeVertexPos[i + j];
            }
            vertex.Normal = normal;
        }
        vertices.push_back(vertex);
    }
    Mesh *mesh = new Mesh(vertices, cubeTriangleIndex, textures);

    mesh->_index = cubeTriangleIndex;
    mesh->_vertexPos = cubeVertexPos;
    mesh->_vertexNormal = cubeVertexNormal;
    mesh->_vertexTexCoord = cubeVertexTexCoord;
    return mesh;
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

    Mesh *mesh = new Mesh();
    mesh->_vertexPos = posVertex;
    mesh->_vertexNormal = normals;
    mesh->_vertexTexCoord = texCoords;
    mesh->_index = indices;
    return mesh;
}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
