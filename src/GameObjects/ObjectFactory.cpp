#include "GameObjects/ObjectFactory.hpp"

#include "Data/BOX.h"

ObjectFactory::ObjectFactory() :
    _GameObjects()
{
    std::cout << "Creating Factory Objects..." << '\n';
}

ObjectFactory::~ObjectFactory() {
    std::cout << "Delete All Game Objects!" << '\n';
    for (unsigned i = 0; i < _GameObjects.size(); ++i) {
        delete _GameObjects[i];
    }
}

void ObjectFactory::addGameObject(GameObject *gameObject) {
    _GameObjects.push_back(gameObject);
};

GameObject* ObjectFactory::getGameObject(unsigned id) {
    return _GameObjects[id];
}

void ObjectFactory::generateDemoObjects() {
    Camera *camera = new Camera();

    std::shared_ptr<MeshRender> meshRender = std::shared_ptr<MeshRender>(new MeshRender());
    std::shared_ptr<Program> program = std::shared_ptr<Program>(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material(meshRender, program));

    meshRender->addMesh(getCubeMesh());

    GameObject* cube1 = new GameObject(1, " *** cube *** ");
    cube1->addComponent(material);
    cube1->translate(glm::vec3(-3.0f, 0.0f, 0.0f));

    GameObject* cube2 = new GameObject(2, " *** cube *** ");
    cube2->addComponent(material);
    cube2->translate(glm::vec3(3.0f, 0.0f, 0.0f));


    std::shared_ptr<MeshRender> meshRender_s = std::shared_ptr<MeshRender>(new MeshRender());
    std::shared_ptr<Material> material_s = std::shared_ptr<Material>(new Material(meshRender_s, program));

    meshRender_s->addMesh(getSphereMesh());

    GameObject *sphere = new GameObject(3, "*** sphere ***");

    sphere->addComponent(material_s);
    sphere->translate(glm::vec3(0.0f, 0.0f, 0.0f));

    _GameObjects.push_back(camera);
    _GameObjects.push_back(cube1);
    _GameObjects.push_back(sphere);
    _GameObjects.push_back(cube2);

/*
    GameObject *cube2 = new GameObject(2, " *** cube *** ");
    _GameObjects.push_back(cube2);

    GameObject *cube3 = new GameObject(3, " *** cube *** ");
    _GameObjects.push_back(cube3);

    GameObject *cube4 = new GameObject(4, " *** cube *** ");
    cube3->_gameObjects.push_back(cube4);

    GameObject *cube5 = new GameObject(5, " *** cube *** ");
    cube3->_gameObjects.push_back(cube5);

    GameObject *cube6 = new GameObject(6, " *** cube *** ");
    cube4->_gameObjects.push_back(cube6);

    GameObject *cube7 = new GameObject(7, " *** cube *** ");
    cube6->_gameObjects.push_back(cube7);
*/
}

Mesh* ObjectFactory::getCubeMesh() {
    Mesh *mesh = new Mesh(1);

    mesh->_vertexPos = cubeVertexPos;
    mesh->_vertexNormal = cubeVertexNormal;
    mesh->_vertexTexCoord = cubeVertexTexCoord;
    mesh->_triangleIndex = cubeTriangleIndex;
    mesh->_NTriangleIndex = cubeTriangleIndex.size();
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
    // Sorting of indices...(for triangles-strip)
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

    Mesh *mesh = new Mesh(2);
    mesh->_vertexPos = posVertex;
    mesh->_vertexNormal = normals;
    mesh->_vertexTexCoord = texCoords;
    mesh->_triangleIndex = indices;
    mesh->_NTriangleIndex = indices.size();
    return mesh;
}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
