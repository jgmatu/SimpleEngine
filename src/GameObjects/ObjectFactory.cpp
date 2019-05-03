#include "GameObjects/ObjectFactory.hpp"

#include "Data/BOX.h"

ObjectFactory::ObjectFactory() :
    _GameObjects()
{
//    std::cout << "Creating Factory Objects..." << '\n';
}

ObjectFactory::~ObjectFactory()
{
//    std::cout << "Delete All Game Objects!" << '\n';

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

std::vector<GameObject*> ObjectFactory::getGameObjects()
{
    return _GameObjects;
}

void ObjectFactory::generateDemoObjects()
{
    // this->simulation1();
    this->solarSystem();
    // this->wallNormalMapping();
}

void ObjectFactory::wallNormalMapping()
{
    Mesh* plane_mesh = getPlaneMesh();

    __Texture__ plane_normal;
    plane_normal.type = "texture_normal";
    plane_normal.path = "../resources/";
    plane_normal.filename = "brickwall_normal.jpg";

    plane_mesh->setTexture(plane_normal);

    GameObject *plane = new GameObject(0, " *** WALL *** ");

    plane->addComponent(new Material(new Model(plane_mesh), new Program("../glsl/wall_vs.glsl", "../glsl/wall_fs.glsl")));
    plane->setPosition(new Position(glm::vec3(1.0, 0.0, 0.0), M_PI / 2.0f));
    plane->setPosition(new Position(glm::vec3(0.0, 0.0, -1.0), M_PI / 12.0f));
    _GameObjects.push_back(plane);
}

void ObjectFactory::solarSystem() {
    GameObject *sun = new GameObject(0, "*** SUN ***");

    sun->setMove(new Translate(glm::vec3(0.0, 0.0, 0.0)));

    sun->addComponent(new Material(new Model(getSphereMesh("sun.png")), new Program("../glsl/sun_vs.glsl", "../glsl/sun_fs.glsl")));
    GameObject *earth = new GameObject(0, "*** EARTH ***");

    earth->setMove(new Rotate(0.3, glm::vec3(0.0, 1.0, 0.0)));
    earth->setMove(new Translate(glm::vec3(-2.0, 0.0, 0.0)));
    earth->setMove(new Rotate(0.8, glm::vec3(0.0, 1.0, -0.5)));
    earth->setMove(new Scale(glm::vec3(0.25, 0.25, 0.25)));

    Mesh *earth_mesh = getSphereMesh("2k_earth_daymap.jpg");

    __Texture__ earth_specular;
    earth_specular.type = "texture_specular";
    earth_specular.path = "../resources/";
    earth_specular.filename = "2k_earth_specular_map.tif";
    earth_mesh->setTexture(earth_specular);

    __Texture__ earth_normal;
    earth_normal.type = "texture_normal";
    earth_normal.path = "../resources/";
    earth_normal.filename = "2k_earth_normal_map.tif";
    earth_mesh->setTexture(earth_normal);

    earth->addComponent(new Material(new Model(earth_mesh), new Program("../glsl/earth_vs.glsl", "../glsl/earth_fs.glsl")));
    earth->addComponent(new Camera());

    GameObject *mars = new GameObject(0, "*** MARS ***");

    mars->setMove(new Rotate(0.3, glm::vec3(0.0, -1.0, 0.0)));
    mars->setMove(new Translate(glm::vec3(3.0, 0.0, 0.0)));
    mars->setMove(new Rotate(0.8, glm::vec3(0.0, -1.0, -0.1)));
    mars->setMove(new Scale(glm::vec3(0.25, 0.25, 0.25)));

    mars->addComponent(new Material(new Model(getSphereMesh("mars.png")), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl")));
    mars->addComponent(new Camera());

    GameObject *moon = new GameObject(0, "*** MOON ***");
    moon->setMove(new Rotate(2.3, glm::vec3(0.0, -1.0, 0.0)));
    moon->setMove(new Translate(glm::vec3(2.0, 0.0, 0.0)));
    moon->setMove(new Rotate(1.8, glm::vec3(0.0, -1.0, 0.0)));
    moon->setMove(new Scale(glm::vec3(0.15, 0.15, 0.15)));

    Mesh *moon_mesh = getSphereMesh("moon.png");

    __Texture__ moon_normal;
    moon_normal.type = "texture_normal";
    moon_normal.path = "../resources/";
    moon_normal.filename = "moon_normal.jpg";
    moon_mesh->setTexture(moon_normal);

    moon->addComponent(new Material(new Model(moon_mesh), new Program("../glsl/moon_vs.glsl", "../glsl/moon_fs.glsl")));
    earth->addGameObject(moon);

    // Skybox :)
    GameObject *skybox = new GameObject(0, "*** SKYBOX ***");
    skybox->addComponent(new SkyBox(std::vector<std::string> {
        "../skybox/ame_nebula/rigth.tga", "../skybox/ame_nebula/left.tga",
        "../skybox/ame_nebula/top.tga", "../skybox/ame_nebula/bottom.tga",
        "../skybox/ame_nebula/front.tga", "../skybox/ame_nebula/back.tga"
    }, new Program("../glsl/skybox_vs.glsl", "../glsl/skybox_fs.glsl")));

    _GameObjects.push_back(sun);

    sun->addGameObject(earth);
    sun->addGameObject(mars);

//    _GameObjects.push_back(mars);
//    _GameObjects.push_back(earth);
    _GameObjects.push_back(skybox);
}

void ObjectFactory::simulation1() {
    std::vector<glm::vec3> cube_positions = {
        glm::vec3(-5.0,  0.0,  0.0),
        glm::vec3(-3.0,  1.0, -1.0),
        glm::vec3(-1.0,  2.0,  2.0),
        glm::vec3( 0.0, -2.0, -1.0),
        glm::vec3( 1.0,  1.0, -1.0)
    };
    std::vector<Movement*> _moves;
    for (unsigned i = 0; i < cube_positions.size(); ++i) {
        _moves.push_back(new Translate(cube_positions[i]));
    }
    for (unsigned i = 0; i < _moves.size(); ++i) {
        GameObject *cube = new GameObject(i + 1, "*** CUBE ***");
        cube->addComponent(new Material(new Model(getCubeMesh()), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl")));
        cube->setMove(_moves[i]);
        cube->addComponent(new Camera());
        _GameObjects.push_back(cube);
    }

    for (unsigned i = 0; i < _moves.size(); ++i) {
        Material *grass = new Material(new Model(getPlantMesh("grass.png")), new Program("../glsl/grass_vs.glsl", "../glsl/grass_fs.glsl"));
        grass->setTransparent();

        GameObject *grass_go = new GameObject(i + 1, "**** GRASS **** ");
        grass_go->addComponent(grass);
        grass_go->setMove(_moves[i]);
        _GameObjects.push_back(grass_go);
    }
    GameObject *_floor_go = new GameObject(0, "*** FLOOR ***");
    _floor_go->addComponent(new Material(new Model(getPlaneMesh()), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl")));
    _floor_go->setMove(new Translate(glm::vec3(0.0, 0.0, 0.0)));
    _GameObjects.push_back(_floor_go);

    Material *nanosuit = new Material(new Model("../models/nanosuit/nanosuit.obj"), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));
    GameObject *nanosuit_go = new GameObject(30, "Complex model");
    nanosuit_go->addComponent(nanosuit);
    nanosuit_go->setMove(new Scale(glm::vec3(0.15, 0.15, 0.15)));
    nanosuit_go->setMove(new Translate(glm::vec3(20.0, 0.0, 0.0)));
    _GameObjects.push_back(nanosuit_go);

}

Mesh* ObjectFactory::getMeshFromVerticesPosTex(std::vector<float> verPosTex, __Texture__ texture)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;

    for (unsigned i = 0; i < verPosTex.size(); i += 5) {
        Vertex vertex;

        vertex.Position = glm::vec3(verPosTex[i], verPosTex[i + 1], verPosTex[i + 2]);
        vertex.Normal = glm::normalize(vertex.Position);
        vertex.TexCoords = glm::vec2(verPosTex[i + 3], verPosTex[i + 4]);
        vertices.push_back(vertex);
    }

    for (unsigned i = 0; i < vertices.size(); ++i) {
        indices.push_back(i);
    }
    std::vector<__Texture__> textures;
    textures.push_back(texture);
    return new Mesh(vertices, indices, textures);
}


std::vector<Mesh*> ObjectFactory::getVerticesRenderBufferTexture()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> cubeVertices = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    std::vector<float> planeVertices = {
        // positions   // texture Coords
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    std::vector<float> quadVertices = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    std::vector<Mesh*> meshes;
    __Texture__ texture;
    texture.path = "../resources/";
    texture.filename = "marble.png";
    meshes.push_back(getMeshFromVerticesPosTex(cubeVertices, texture));

    texture.path = "../resources/";
    texture.filename = "floor.jpg";
    meshes.push_back(getMeshFromVerticesPosTex(planeVertices, texture));
    meshes.push_back(getMeshFromVerticesPosTex(quadVertices, texture));
    return meshes;
}

Mesh* ObjectFactory::getPlantMesh(std::string texture_diffuse) {
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
        vertex.Normal = glm::vec3(0.0, 0.0, 1.0);
        vertex.TexCoords = glm::vec2(textCoords[j], textCoords[j + 1]);
        vertices.push_back(vertex);
    }

    std::vector<__Texture__> textures;
    __Texture__ texture;
    texture.path = "../resources/";
    texture.filename = texture_diffuse;
    textures.push_back(texture);

    return new Mesh(vertices, inidices, textures);
}

Mesh* ObjectFactory::getPlaneMesh() {
/*    std::vector<GLfloat> position = {
         1.0f, -0.5f,  1.0f, // 0
        -1.0f, -0.5f,  1.0f, // 1
        -1.0f, -0.5f, -1.0f, // 2

         1.0f, -0.5f,  1.0f, // 3
        -1.0f, -0.5f, -1.0f, // 4
         1.0f, -0.5f, -1.0f  // 5
    };
    std::vector<GLuint> indices = {
        1, 2, 0,
        4, 2, 3,
        5, 4, 3,
        2, 5, 1
    };
    std::vector<GLfloat> textCoord = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };
*/
    std::vector<GLfloat> position = {
        -1.0f,  1.0f,  0.0f, // 0
        -1.0f, -1.0f,  0.0f, // 1
         1.0f, -1.0f,  0.0f, // 2
         1.0f,  1.0f,  1.0f, // 3
    };
    std::vector<GLuint> indices = {
        0, 1, 2,
        0, 2, 3
    };
    std::vector<GLfloat> textCoord = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
    std::vector<Vertex> vertices;
    for (unsigned i = 0, j = 0; i < position.size(); i += 3, j += 2) {
        Vertex vertex;

        vertex.Position = glm::vec3(position[i], position[i + 1], position[i + 2]);
        vertex.Normal = glm::normalize(glm::vec3(0.0, 0.0, 1.0));
        vertex.TexCoords = glm::vec2(textCoord[j], textCoord[j + 1]);
        vertices.push_back(vertex);
    }
    std::vector<__Texture__> textures;

    __Texture__ texture;
    texture.path = "../resources/";
    texture.filename = "brickwall.jpg";
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

Mesh* ObjectFactory::getSphereMesh(std::string filename) {
    int idx = 0;
    std::vector<std::vector<int>> grid;

    // Buffers...
    std::vector<GLfloat> posVertex;
    std::vector<GLfloat> normals;
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
                vertex.x = radius * cos( u * M_PI * 2.0f ) * sin( v * M_PI );

                // Vertex. Y.
                vertex.y = radius * cos( v * M_PI );

                // Vertex. Z.
                vertex.z = radius * sin( u * M_PI * 2.0f ) * sin( v * M_PI );

                GLfloat aux[] = {-vertex.x, -vertex.y, -vertex.z};
                posVertex.insert(posVertex.end(), aux, aux + 3);

                // Normal.
                glm::vec3 normal(vertex);
                normal = glm::normalize(normal); // Normalize... Here!

                GLfloat norm[] = {normal.x, normal.y, normal.z};
                normals.insert(normals.end(), norm, norm + 3);

                // TexCoord. Is good because draw the first texture...
                double texCoord[] = {u, 1.0 - v};

                Vertex vertex;
                vertex.Position = glm::vec3(aux[0], aux[1], aux[2]);
                vertex.TexCoords = glm::vec2(texCoord[0], texCoord[1]);
                vertex.Normal = normal;

                vertices.insert(vertices.end(), vertex);

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

                int aux2[] = {b, c, d};
                indices.insert(indices.end(), aux2, aux2 + 3);
          }
    }
    std::vector<__Texture__> textures;

    __Texture__ texture;

    texture.type = "texture_diffuse";
    texture.path = "../resources/";
    texture.filename = filename;
    textures.push_back(texture);

//    texture.type = "texture_specular";
//    texture.path = "../resources/";
//    texture.filename = "container2_specular.png";
//    textures.push_back(texture);

    return new Mesh(vertices, indices, textures);
}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
