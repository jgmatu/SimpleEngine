#include "Drawers/Skybox.hpp"

const float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

SkyBox::SkyBox()
{
    this->_uniforms = new Uniforms();
    this->_program = new Program("../glsl/utils/skybox_vs.glsl", "../glsl/utils/skybox_fs.glsl", true);
}

SkyBox::SkyBox(std::vector<std::string> faces) :
    SkyBox::SkyBox()
{
    this->_faces = faces;
}

SkyBox::~SkyBox()
{
    std::cerr << "Delete Skybox" << '\n';
    delete _uniforms;
}

void SkyBox::active()
{
    std::cerr << "Active Skybox" << '\n';
    _program->active();

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    _textureID = Texture::TextureCubeMap(_faces);
}

void SkyBox::draw()
{
    _program->use();
    _program->update(_uniforms);

    glDepthMask(GL_FALSE);

    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    glBindVertexArray(_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default

    glDepthMask(GL_TRUE);
}

void SkyBox::setView(Camera *camera)
{
    this->setParameter("projection", camera->_projection); // Vertex...
    this->setParameter("view", glm::mat4(glm::mat3(camera->_view->_gModel)));      // Vertex...
    this->setParameter("skybox", 0); // Fragments...
}

void SkyBox::setParameter(std::string name, glm::vec3 val) {
    _uniforms->setUniformVec3(name, val);
}

void SkyBox::setParameter(std::string name, glm::mat4 val) {
    _uniforms->setUniformMat4(name, val);
}

void SkyBox::setParameter(std::string name, int val) {
    _uniforms->setUniformInt(name, val);
}

void SkyBox::setParameter(std::string name, float val) {
    _uniforms->setUniformFloat(name, val);
}
