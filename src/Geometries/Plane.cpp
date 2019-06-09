#include <Geometries/Plane.hpp>

Plane::Plane(std::string id_mesh)
{
    generatePlaneMesh(id_mesh);
}

Plane::~Plane()
{
    delete _mesh;
}

Mesh* Plane::getMesh()
{
    return Geometry::getMesh();
}

void Plane::generatePlaneMesh(std::string id_mesh)
{
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
    for (uint32_t i = 0, j = 0; i < position.size(); i += 3, j += 2) {
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
    this->_mesh = new Mesh(id_mesh, vertices, indices);
}
