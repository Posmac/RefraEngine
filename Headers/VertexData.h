#ifndef REFRAENGINE_VERTEXDATA_H
#define REFRAENGINE_VERTEXDATA_H

#include <glm/glm.hpp>

namespace rfe
{
    //vertex data (P)osition, (T)exture, (N)ormal
    struct VertexDataPTN {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 textureCoord;
    public:
        VertexDataPTN();
        VertexDataPTN(const glm::vec3& pos, const glm::vec3& norm,const glm::vec2& text);
    };
}

#endif //REFRAENGINE_VERTEXDATA_H
