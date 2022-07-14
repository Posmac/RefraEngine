#include "VertexData.h"

rfe::VertexDataPTN::VertexDataPTN(const glm::vec3& pos, const glm::vec3& norm,
                                  const glm::vec2& text) {
    position = pos;
    normal = norm;
    textureCoord = text;
}

rfe::VertexDataPTN::VertexDataPTN() {
    position = glm::vec3(0.0);
    normal = glm::vec3(0.0);
    textureCoord = glm::vec3(0.0);
}
