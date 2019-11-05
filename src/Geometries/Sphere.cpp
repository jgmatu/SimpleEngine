#include <Geometries/Sphere.hpp>
#include <iomanip>      // std::setprecision

Sphere::Sphere(std::string id_mesh)
{
    generateSphereMesh(id_mesh);
}


Mesh* Sphere::getMesh()
{
    return Geometry::getMesh();
}

void Sphere::generateSphereMesh(std::string id_mesh)
{
    std::vector<GLfloat> posVertex;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;

    float radius = 10.0f;

    float lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorCount = 100.0f;
    float stackCount = 100.0f;

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;

    float phy, theta;

    std::vector<Vertex> vertices;

    // Generate vertices, normals and texCoords
    for (int i = 0; i <= stackCount; ++i) {
          std::vector<int> verticesRow;

          phy = M_PI / 2 - i * stackStep;

          for (int j = 0; j <= sectorCount; ++j) {
                theta =  j * sectorStep;

                // Vertex. X.
                float x = radius * cosf( phy ) * cosf( theta );

                // Vertex. Y.
                float y = radius * cosf( phy ) * sinf( theta );

                // Vertex. Z.
                float z = radius * sinf( phy );

                std::cout << "v " << std::fixed << x << " " << y << " " << z << '\n';

                GLfloat aux[] = {x, y, z};
                posVertex.insert(posVertex.end(), aux, aux + 3);

                // Normal.
                glm::vec3 normal;

                normal.x = x * lengthInv;
                normal.y = y * lengthInv;
                normal.z = z * lengthInv;

                std::cout << "vn " << std::fixed << normal.x << " " << normal.y << " " << normal.z << '\n';
                normal = glm::normalize(normal);

                GLfloat norm[] = {normal.x, normal.y, normal.z};
                normals.insert(normals.end(), norm, norm + 3);

                // TexCoord. Is good because draw the first texture...
                s = (float) j / sectorCount;
                t = (float) i / stackCount;
                double texCoord[] = {s, t};

                std::cout << "vt "<< std::fixed << s << " " << t << '\n';

                Vertex vertex;
                vertex.Position = glm::vec3(aux[0], aux[1], aux[2]);
                vertex.TexCoords = glm::vec2(texCoord[0], texCoord[1]);
                vertex.Normal = normal;

                vertices.insert(vertices.end(), vertex);
          }
    }

    // generate CCW index list of sphere triangles
    int k1, k2;
    for (uint32_t i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (uint32_t j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != stackCount - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    for (uint32_t i = 0; i < indices.size(); ++i) {
        if (i % 3 == 0) {
            std::cout << "\nf ";
        }
        std::cout << indices[i] << ' ';
    }
    std::cout << '\n';
    this->_mesh = new Mesh(id_mesh, vertices, indices);
}
