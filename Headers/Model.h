#ifndef REFRAENGINE_MODEL_H
#define REFRAENGINE_MODEL_H

#include "Mesh.h"
#include "Shader.h"

namespace rfe {
    class Model {
    private:
        const rfe::Mesh* mesh;
        rfe::Shader* shader;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        float angle;
        glm::mat4 model;
    public:
        Model(const rfe::Mesh& mesh, rfe::Shader& shader);
        void Transform(const glm::vec3& position);
        void Translate(const glm::vec3& add);
        void Scale(const glm::vec3& scale);
        void Rotate(const glm::vec3& rotation, float angle);
        void ResetModelMatrix();
        void DrawModel();

        void SetupShaderModelMatrix();
    };
}


#endif //REFRAENGINE_MODEL_H
