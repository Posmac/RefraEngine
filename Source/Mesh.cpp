#include "Mesh.h"

rfe::VertexDataPTN::VertexDataPTN(const glm::vec3& pos, const glm::vec3& norm,
                                  const glm::vec2& text) {
    position = pos;
    normal = norm;
    textureCoord = text;
}

rfe::VertexDataPTN::VertexDataPTN() {

}

rfe::Mesh::Mesh() {

    //generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //Copy data to buffer
    //First Vertex data
    glBufferData(GL_ARRAY_BUFFER, meshVertexData.size() * sizeof(VertexDataPTN), &meshVertexData[0], GL_STATIC_DRAW);
    //Second index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //setup data reading
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPTN), (void*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDataPTN), (void*)(offsetof(VertexDataPTN, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexDataPTN), (void*)(offsetof(VertexDataPTN, textureCoord)));

    glBindVertexArray(0);
}

void rfe::Mesh::AddVertexData(const VertexDataPTN& vertexDataPtn) {
    meshVertexData.push_back(vertexDataPtn);
}

void rfe::Mesh::AddIndex(int index) {
    indices.push_back(index);
}
