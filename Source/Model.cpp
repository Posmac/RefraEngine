
#include "Model.h"

rfe::Model::Model(const rfe::Mesh& mesh) {
    this->mesh = &mesh;
}

void rfe::Model::DrawModel(rfe::Shader& shader) {
    mesh->Bind();
    glDrawElements(GL_TRIANGLES, mesh->GetVertexCount(), GL_UNSIGNED_INT, 0);
    mesh->Unbind();
}
