#ifndef REFRAENGINE_MODEL_H
#define REFRAENGINE_MODEL_H

#include "Mesh.h"
#include "Shader.h"

namespace rfe {
    class Model {
    private:
        const rfe::Mesh* mesh;
    public:
        Model(const rfe::Mesh& mesh);
        void DrawModel(Shader& shader);
    };
}


#endif //REFRAENGINE_MODEL_H
