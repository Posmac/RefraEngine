#include "Model.h"

rfe::Model::Model(const rfe::Mesh& mesh, rfe::Shader& shader) {
    this->mesh = &mesh;
    this->shader = &shader;
    model = glm::mat4(1.0);
}

void rfe::Model::DrawModel(rfe::Shader& shader) {
    mesh->Bind();
    glDrawElements(GL_TRIANGLES, mesh->GetVertexCount(), GL_UNSIGNED_INT, 0);
    mesh->Unbind();
}

void rfe::Model::Transform(const glm::vec3& position) {
    this->position = position;
}

void rfe::Model::Translate(const glm::vec3& add) {
    position += add;
}

void rfe::Model::Scale(const glm::vec3& scale) {
    this->scale = scale;
}

void rfe::Model::Rotate(const glm::vec3& rotation, float angle) {
    this->rotation = rotation;
    this->angle = angle;
}

void rfe::Model::ResetModelMatrix() {
    model = glm::mat4(1.0);
}

void rfe::Model::SetupShaderModelMatrix() {
    shader->SetMatrix4fUniform("model", model);
}
