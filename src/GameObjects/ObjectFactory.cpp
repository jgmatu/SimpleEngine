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

    MeshRender *meshRender_sun = new MeshRender();
    MeshRender *meshRender_earth = new MeshRender();
    MeshRender *meshRender_moon = new MeshRender();
    MeshRender *meshRender_mars = new MeshRender();
    MeshRender *meshRender_mercury = new MeshRender();
    MeshRender *meshRender_jupiter = new MeshRender();

    meshRender_sun->addMesh(getSphereMesh("** SUN **"));
    meshRender_earth->addMesh(getSphereMesh("** EARTH **"));
    meshRender_moon->addMesh(getSphereMesh("** MOON **"));
    meshRender_mars->addMesh(getSphereMesh("** MARS **"));
    meshRender_mercury->addMesh(getSphereMesh("*** MERCURY ***"));
    meshRender_jupiter->addMesh(getSphereMesh("*** JUPITER ***"));

    Program *program = new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl");

    Material *material_sun = new Material(meshRender_sun, program);
    Material *material_earth = new Material(meshRender_earth, program);
    Material *material_moon = new Material(meshRender_moon, program);
    Material *material_mars = new Material(meshRender_mars, program);
    Material *material_mercury = new Material(meshRender_mercury, program);
    Material *material_jupiter = new Material(meshRender_jupiter, program);


    GameObject *sun = new GameObject(1, " *************************** SUN ********************************** ");
    GameObject *earth = new GameObject(2, " ************************ EARTH ********************************* ");
    GameObject *moon = new GameObject(3, " ************************* MOON ********************************** ");
    GameObject *mars = new GameObject(4, " ************************* MARS ********************************** ");
    GameObject *mercury = new GameObject(5, " ************************* MERCURY **************************** ");
    GameObject *jupiter = new GameObject(6, " ************************* JUPITER **************************** ");

    _GameObjects.push_back(camera);
    _GameObjects.push_back(sun);

    sun->addGameObject(earth);
    sun->addGameObject(mars);
    sun->addGameObject(mercury);
    sun->addGameObject(jupiter);

    earth->addGameObject(moon);

    sun->addComponent(material_sun);
    earth->addComponent(material_earth);
    moon->addComponent(material_moon);
    mars->addComponent(material_mars);
    mercury->addComponent(material_mercury);
    jupiter->addComponent(material_jupiter);
}

Mesh* ObjectFactory::getCubeMesh() {
    Mesh *mesh = new Mesh(1, "cube");

    mesh->_vertexPos = cubeVertexPos;
    mesh->_vertexNormal = cubeVertexNormal;
    mesh->_vertexTexCoord = cubeVertexTexCoord;
    mesh->_triangleIndex = cubeTriangleIndex;
    mesh->_NTriangleIndex = cubeTriangleIndex.size();
    return mesh;
}

Mesh* ObjectFactory::getSphereMesh(std::string name) {
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

    Mesh *mesh = new Mesh(1, name);
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
