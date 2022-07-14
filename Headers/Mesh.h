#ifndef REFRAENGINE_MESH_H
#define REFRAENGINE_MESH_H

#include "Render.h"
#include "VertexData.h"
#include <string>
#include <vector>

namespace rfe {
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
