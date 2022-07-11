#ifndef REFRAENGINE_MESH_H
#define REFRAENGINE_MESH_H

#include "Render.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>

namespace rfe {
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

    class Mesh {
    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        std::vector<VertexDataPTN> meshVertexData;
        std::vector<unsigned int> indices;
    public:
        Mesh();
        void CreateMeshVAO();
        void AddVertexData(const VertexDataPTN& vertexDataPtn);
        void AddIndex(unsigned int index);
        void Bind() const;
        void Unbind()const;
        int GetVertexCount() const;
    };
}

#endif //REFRAENGINE_MESH_H
