#include "Mesh.h"

rfe::Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
}

void rfe::Mesh::CreateMeshVAO()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, meshVertexData.size() * sizeof(VertexDataPTN), &meshVertexData[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPTN), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPTN), (void*)(offsetof(VertexDataPTN, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexDataPTN), (void*)(offsetof(VertexDataPTN, textureCoord)));

    glBindVertexArray(0);
}

void rfe::Mesh::AddVertexData(const VertexDataPTN& vertexDataPtn) {
    meshVertexData.push_back(vertexDataPtn);
}

void rfe::Mesh::AddIndex(unsigned int index) {
    indices.push_back(index);
}

void rfe::Mesh::Bind() const {
    glBindVertexArray(VAO);
}

void rfe::Mesh::Unbind() const {
    glBindVertexArray(0);
}

int rfe::Mesh::GetVertexCount() const {
    return indices.size();
}
