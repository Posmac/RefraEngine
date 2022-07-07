#ifndef REFRAENGINE_CAMERA_H
#define REFRAENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace rfe
{
    class Camera
    {
    private:
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 up;

        float yaw;
        float pitch;
        float roll;
    public:
        Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up,
               float yaw = 0, float pitch = 0, float roll = 0);
        void Translate(const glm::vec3& newPosition);
        glm::mat4 StaticViewMatrix(const glm::vec3 targetPosition);
        glm::mat4 DynamicViewMatrix();
        glm::mat4 ProjectionMatrix();
    };
}

#endif //REFRAENGINE_CAMERA_H
