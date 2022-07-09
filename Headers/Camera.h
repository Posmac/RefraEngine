#ifndef REFRAENGINE_CAMERA_H
#define REFRAENGINE_CAMERA_H

#include "Input.h"
#include <glm/glm.hpp>

namespace rfe
{
    class Camera
    {
    private:
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;

        float speed;

        MouseData lastMouseData;
        bool firstMove;
        float yaw;
        float pitch;
        float roll;
    public:
        Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float speed,
               float yaw = -90, float pitch = 0, float roll = 0);
        void Translate(const glm::vec3& newPosition);
        glm::mat4 ViewMatrix();
        glm::mat4 PerspectiveMatrix(float angleInDeg, float aspect, float near, float far);
        glm::mat4 OrthogonalMatrix(float sizeX, float sizeY, float near, float far);
        void ProcessInput(Input& input, float deltaTime);
        void ProcessMouseInput(MouseData mouseData, float deltaTime, float sensivity);
        void SetCursorFPS(rfe::Window& window);
        void RecalculateBasisVectors();
    };
}

#endif //REFRAENGINE_CAMERA_H
