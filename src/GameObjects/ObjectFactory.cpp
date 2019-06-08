#include "GameObjects/ObjectFactory.hpp"

#include "Data/BOX.h"

ObjectFactory::ObjectFactory() :
    _GameObjects()
{
//    std::cout << "Creating Factory Objects..." << '\n';
}

ObjectFactory::~ObjectFactory()
{
//    std::cout << "Delete All Game Objects!" << '\n'
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
    this->simulation1();
//    this->solarSystem();
    // this->wallNormalMapping();
}

void ObjectFactory::wallNormalMapping()
{
    Mesh* plane_mesh = getPlaneMesh("plane_mesh");

    GameObject *plane = new GameObject(0, " *** WALL *** ");
    Material *material = new Material(new Model(plane_mesh));
    material->setProgram(new Program("../glsl/wall_vs.glsl", "../glsl/wall_fs.glsl"));

    __Texture__ *plane_diffuse = new __Texture__();
    plane_diffuse->type = "texture_normal";
    plane_diffuse->path = "../resources/";
    plane_diffuse->filename = "brickwall.jpg";
    material->setTexture("plane_mesh", plane_diffuse);

    __Texture__ *plane_normal = new __Texture__();
    plane_normal->type = "texture_normal";
    plane_normal->path = "../resources/";
    plane_normal->filename = "brickwall_normal.jpg";
    material->setTexture("plane_mesh", plane_normal);

    plane->addComponent(material);
    plane->setMove(new Rotate(0.8, glm::vec3(1.0, 0.0, 0.0)));
//    plane->setPosition(new Position(glm::vec3(1.0, 0.0, 0.0), M_PI / 2.0f));
//    plane->setPosition(new Position(glm::vec3(0.0, 0.0, -1.0), M_PI / 12.0f));
    _GameObjects.push_back(plane);
}

void ObjectFactory::solarSystem() {
//{
    // SUN
    GameObject *sun = new GameObject(0, "*** SUN ***");

    Material *material_sun = new Material(new Model(getSphereMesh("mesh_sphere")));
    material_sun->setProgram(new Program("../glsl/sun_vs.glsl", "../glsl/sun_fs.glsl"));

    __Texture__ *sun_diffuse = new __Texture__();
    sun_diffuse->type = "texture_diffuse";
    sun_diffuse->path = "../resources/";
    sun_diffuse->filename = "sun.png";
    material_sun->setTexture("mesh_sphere", sun_diffuse);

    sun->setMove(new Translate(glm::vec3(0.0, 0.0, 0.0)));
    sun->addComponent(material_sun);
//}

//{
    // EARTH
    GameObject *earth = new GameObject(0, "*** EARTH ***");

    earth->setMove(new Rotate(0.3, glm::vec3(0.0, 1.0, 0.0)));
    earth->setMove(new Translate(glm::vec3(-2.0, 0.0, 0.0)));
    earth->setMove(new Rotate(0.8, glm::vec3(0.0, 1.0, -0.5)));
    earth->setMove(new Scale(glm::vec3(0.25, 0.25, 0.25)));

    Material *material_earth = new Material(new Model(getSphereMesh("mesh_sphere")));
    material_earth->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    __Texture__ *earth_diffuse = new __Texture__();
    earth_diffuse->type = "texture_diffuse";
    earth_diffuse->path = "../resources/";
    earth_diffuse->filename = "2k_earth_daymap.jpg";
    material_earth->setTexture("mesh_sphere", earth_diffuse);

    __Texture__ *earth_specular = new __Texture__();
    earth_specular->type = "texture_specular";
    earth_specular->path = "../resources/";
    earth_specular->filename = "2k_earth_specular_map.tif";
//    material_earth->setTexture("mesh_sphere", earth_specular);

    __Texture__ *earth_normal = new __Texture__();
    earth_normal->type = "texture_normal";
    earth_normal->path = "../resources/";
    earth_normal->filename = "2k_earth_normal_map.tif";
//    material_earth->setTexture("mesh_sphere", earth_normal);

    earth->addComponent(material_earth);
    earth->addComponent(new Camera());

//}

//{
    // MARS
    GameObject *mars = new GameObject(0, "*** MARS ***");

    mars->setMove(new Rotate(0.3, glm::vec3(0.0, -1.0, 0.0)));
    mars->setMove(new Translate(glm::vec3(3.0, 0.0, 0.0)));
    mars->setMove(new Rotate(0.8, glm::vec3(0.0, -1.0, -0.1)));
    mars->setMove(new Scale(glm::vec3(0.25, 0.25, 0.25)));

    Material *material_mars = new Material(new Model(getSphereMesh("mesh_sphere")));
    material_mars->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    __Texture__ *mars_diffuse = new __Texture__();
    mars_diffuse->type = "texture_diffuse";
    mars_diffuse->path = "../resources/";
    mars_diffuse->filename = "mars.png";
    material_mars->setTexture("mesh_sphere", mars_diffuse);

    mars->addComponent(material_mars);
    mars->addComponent(new Camera());
//}

//{
    // *** MOON ***
    GameObject *moon = new GameObject(0, "*** MOON ***");
    moon->setMove(new Rotate(2.3, glm::vec3(0.0, -1.0, 0.0)));
    moon->setMove(new Translate(glm::vec3(2.0, 0.0, 0.0)));
    moon->setMove(new Rotate(1.8, glm::vec3(0.0, -1.0, 0.0)));
    moon->setMove(new Scale(glm::vec3(0.15, 0.15, 0.15)));

    Material *material_moon = new Material(new Model(getSphereMesh("mesh_sphere")));
    material_moon->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    __Texture__ *moon_diffuse = new __Texture__();
    moon_diffuse->type = "texture_diffuse";
    moon_diffuse->path = "../resources/";
    moon_diffuse->filename = "moon.png";
    material_moon->setTexture("mesh_sphere", moon_diffuse);

    moon->addComponent(material_moon);
    earth->addGameObject(moon);
//}

    // Skybox :)
    GameObject *skybox = new GameObject(0, "*** SKYBOX ***");
    skybox->addComponent(new SkyBox(std::vector<std::string> {
        "../skybox/ame_nebula/rigth.tga", "../skybox/ame_nebula/left.tga",
        "../skybox/ame_nebula/top.tga", "../skybox/ame_nebula/bottom.tga",
        "../skybox/ame_nebula/front.tga", "../skybox/ame_nebula/back.tga"
    }, new Program("../glsl/skybox_vs.glsl", "../glsl/skybox_fs.glsl")));
    skybox->setMove(new Scale(glm::vec3(10.0, 10.0, 10.0)));

    _GameObjects.push_back(sun);
    _GameObjects.push_back(skybox);
    sun->addGameObject(earth);
    sun->addGameObject(mars);
}

void ObjectFactory::simulation1() {
    std::vector<glm::vec3> cube_positions = {
        glm::vec3(-1.0,  0.0,  0.0)
//        glm::vec3(-1.0,  1.1,  0.0),
//        glm::vec3(-1.0,  2.2,  0.0),
//        glm::vec3(-1.0, -1.3,  0.0),
//        glm::vec3(-1.0, -2.4,  0.0)
    };
    std::vector<Movement*> _moves;
    for (unsigned i = 0; i < cube_positions.size(); ++i) {
        _moves.push_back(new Translate(cube_positions[i]));
    }

    for (unsigned i = 0; i < cube_positions.size(); ++i) {
        GameObject *cube = new GameObject(i + 1, "*** CUBE ***");

        std::string id_mesh = "cube_mesh";
        Material *material = new Material(new Model(getCubeMesh(id_mesh)));
        material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

        __Texture__ *diffuse = new __Texture__();
        diffuse->type = "texture_diffuse";
        diffuse->path = "../resources";
        diffuse->filename = "container2.png";
        material->setTexture(id_mesh, diffuse);

        __Texture__ *specular = new __Texture__();
        specular->type = "texture_specular";
        specular->path = "../resources";
        specular->filename = "container2_specular.png";
        material->setTexture(id_mesh, specular);

        cube->addComponent(material);
        cube->addComponent(new Camera());

        cube->setMove(_moves[i]);
        _GameObjects.push_back(cube);

        std::cout << "/* message ********************/" << '\n';
    }

//    for (unsigned i = 0; i < _moves.size(); ++i) {
//        Material *grass = new Material(new Model(getPlantMesh("grass.png")), new Program("../glsl/grass_vs.glsl", "../glsl/grass_fs.glsl"));
//        grass->setTransparent();

//        GameObject *grass_go = new GameObject(i + 1, "**** GRASS **** ");
//        grass_go->addComponent(grass);
//        grass_go->setMove(_moves[i]);
//        _GameObjects.push_back(grass_go);
//    }
//    GameObject *_floor_go = new GameObject(0, "*** FLOOR ***");
//    _floor_go->addComponent(new Material(new Model(getPlaneMesh()), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl")));
//    _floor_go->setMove(new Translate(glm::vec3(0.0, 0.0, 0.0)));
//    _GameObjects.push_back(_floor_go);

//    Material *nanosuit = new Material(new Model("../models/nanosuit/nanosuit.obj"), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));
//    GameObject *nanosuit_go = new GameObject(30, "Complex model");
//    nanosuit_go->addComponent(nanosuit);
//    nanosuit_go->setMove(new Scale(glm::vec3(0.15, 0.15, 0.15)));
//    nanosuit_go->setMove(new Translate(glm::vec3(20.0, 0.0, 0.0)));
//    _GameObjects.push_back(nanosuit_go);

}

Mesh* ObjectFactory::getMeshFromVerticesPosTex(std::string id_mesh, std::vector<float> verPosTex)
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
    return new Mesh(id_mesh, vertices, indices);
}

Mesh* ObjectFactory::getPlantMesh(std::string id_mesh) {
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
    return new Mesh(id_mesh, vertices, inidices);
}

Mesh* ObjectFactory::getPlaneMesh(std::string id_mesh) {
    std::vector<GLfloat> position = {
        -1.0f,  1.0f,  0.0f, // 0
        -1.0f, -1.0f,  0.0f, // 1
         1.0f, -1.0f,  0.0f, // 2
         1.0f,  1.0f,  0.0f, // 3
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

    for (unsigned i = 0; i < vertices.size(); ++i) {
        glm::vec3 edge1 = vertices[(i + 1) % vertices.size()].Position - vertices[i].Position;
        glm::vec3 edge2 = vertices[(i + 2) % vertices.size()].Position - vertices[i].Position;
        glm::vec2 deltaUV1 = vertices[(i + 1) % vertices.size()].TexCoords - vertices[i].TexCoords;
        glm::vec2 deltaUV2 = vertices[(i + 2) % vertices.size()].TexCoords - vertices[i].TexCoords;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        vertices[i].Tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        vertices[i].Tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        vertices[i].Tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        vertices[i].Tangent = glm::normalize(vertices[i].Tangent);
    }
    return new Mesh(id_mesh, vertices, indices);
}

void ObjectFactory::getTBNMatrix() {
//    glm::vec3 edge1 = pos2 - pos1;
//    glm::vec3 edge2 = pos3 - pos1;
//    glm::vec2 deltaUV1 = uv2 - uv1;
//    glm::vec2 deltaUV2 = uv3 - uv1;
    ;
}

Mesh* ObjectFactory::getCubeMesh(std::string id_mesh) {
    std::vector<__Texture__> textures(2);
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices = cubeTriangleIndex;

    for (unsigned i = 0, j = 0; i < __cubeVertices.size(); i += 5, j += 3) {
        Vertex vertex;

        glm::vec3 normal;
        glm::vec3 position;
        glm::vec2 text;

        position.x = __cubeVertices[i];
        position.y = __cubeVertices[i + 1];
        position.z = __cubeVertices[i + 2];
        text.x = __cubeVertices[i + 3];
        text.y = __cubeVertices[i + 4];

        normal.x = cubeVertexNormal[j];
        normal.y = cubeVertexNormal[j + 1];
        normal.z = cubeVertexNormal[j + 2];

        vertex.Normal = normal;
        vertex.Position = position;
        vertex.TexCoords = text;
        vertices.push_back(vertex);
    }
    return new Mesh(id_mesh, vertices, indices);
}

Mesh* ObjectFactory::getSphereMesh(std::string id_mesh)
{
    std::vector<GLfloat> posVertex;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;

    float radius = 1.0f;

    float lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorCount = 100.0f;
    float stackCount = 100.0f;

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;

    float phy, theta;


    glm::vec3 vertex(1.0f); // Row vec3...
    std::vector<Vertex> vertices;

    // Generate vertices, normals and texCoords
    for (int i = 0; i <= stackCount; ++i) {
          std::vector<int> verticesRow;

          phy = M_PI / 2 - i * stackStep;

          for (int j = 0; j <= sectorCount; ++j) {
                theta =  j * sectorStep;

                // Vertex. X.
                vertex.x = radius * cosf( phy ) * cosf( theta );

                // Vertex. Y.
                vertex.y = radius * cosf( phy ) * sinf( theta );

                // Vertex. Z.
                vertex.z = radius * sinf( phy );

                GLfloat aux[] = {vertex.x, vertex.y, vertex.z};
                posVertex.insert(posVertex.end(), aux, aux + 3);

                // Normal.
                glm::vec3 normal;

                normal.x = vertex.x * lengthInv;
                normal.y = vertex.y * lengthInv;
                normal.z = vertex.z * lengthInv;
                normal = glm::normalize(normal);

                GLfloat norm[] = {normal.x, normal.y, normal.z};
                normals.insert(normals.end(), norm, norm + 3);

                // TexCoord. Is good because draw the first texture...
                s = (float) j / sectorCount;
                t = (float) i / stackCount;
                double texCoord[] = {s, t};

                Vertex vertex;
                vertex.Position = glm::vec3(aux[0], aux[1], aux[2]);
                vertex.TexCoords = glm::vec2(texCoord[0], texCoord[1]);
                vertex.Normal = normal;

                vertices.insert(vertices.end(), vertex);
          }
    }

    // generate CCW index list of sphere triangles
    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != stackCount - 1)
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    return new Mesh(id_mesh, vertices, indices);
}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
