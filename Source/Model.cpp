#include "Model.h"

rfe::Model::Model(const rfe::Mesh& mesh, rfe::Shader& shader) {
    this->mesh = &mesh;
    this->shader = &shader;
    model = glm::mat4(1.0);
}

void rfe::Model::DrawModel() {
    mesh->Bind();
    glDrawElements(GL_TRIANGLES, mesh->GetVertexCount(), GL_UNSIGNED_INT, 0);
    mesh->Unbind();
}

void rfe::Model::Transform(const glm::vec3& position) {
    this->position = position;
    model = glm::translate(model, position);
}

void rfe::Model::Translate(const glm::vec3& add) {
    position += add;
    model = glm::translate(model, position);
}

void rfe::Model::Scale(const glm::vec3& scale) {
    this->scale = scale;
    model = glm::scale(model, scale);
}

void rfe::Model::Rotate(const glm::vec3& rotation, float angle) {
    this->rotation = rotation;
    this->angle = angle;
    model = glm::rotate(model, glm::radians(angle), rotation);
}

void rfe::Model::ResetModelMatrix() {
    position = glm::vec3(0);
    scale = glm::vec3(1.0);
    rotation = glm::vec3(0.0);
    angle = 0;
    model = glm::mat4(1.0);
}

void rfe::Model::SetupShaderModelMatrix() {
    shader->SetMatrix4fUniform("model", model);
}
