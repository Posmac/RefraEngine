#include "Camera.h"

rfe::Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float speed,
                    float yaw, float pitch, float roll)
    : position(position), forward(forward), worldUp(up),
    yaw(yaw), pitch(pitch), roll(roll), speed(speed)
{
    firstMove = false;
}

void rfe::Camera::Translate(const glm::vec3 &newPosition)
{
    position += newPosition;
}

glm::mat4 rfe::Camera::ViewMatrix()
{
    glm::vec3 z = glm::normalize(forward); //forward vector
    glm::vec3 x = glm::normalize(glm::cross(z, up)); // right vector
    glm::vec3 y = glm::cross(x, z); // up vector

    glm::mat4 lookAtRH = {
            glm::vec4(x.x, y.x, -z.x, 0),
            glm::vec4(x.y, y.y, -z.y, 0),
            glm::vec4(x.z, y.z, -z.z, 0),
            glm::vec4(-glm::dot(x, position), -glm::dot(y, position) , glm::dot(z, position), 1),
    };

    return lookAtRH;
}

glm::mat4 rfe::Camera::PerspectiveMatrix(float angleInDeg, float aspect, float near, float far) {
    float t = near * tan(glm::radians(angleInDeg/2));
    float r = t * aspect;
    float ze = (far + near) / (near - far);
    float zd = 2*near*far/(near - far);
    glm::mat4 result = glm::mat4(1.0);
    result[0][0] = near / r;
    result[1][1] = near / t;
    result[2][2] = ze;
    result[3][2] = zd;
    result[2][3] = -1;
    return result;
}

glm::mat4 rfe::Camera::OrthogonalMatrix(float sizeX, float sizeY, float near, float far) {
    glm::mat4 result(1.0);
    result[0][0] = 1/(sizeX/2);
    result[1][1] = 1/(sizeY/2);
    result[2][2] = -2/(far-near);
    result[3][2] = (far - near)/(near - far);
    return result;
}

void rfe::Camera::ProcessInput(rfe::Input& input, float deltaTime) {
    if(input.GetKeyState(rfe::KEY_W) == rfe::Pressed)
    {
        Translate(forward * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_S) == rfe::Pressed)
    {
        Translate(-forward * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_A) == rfe::Pressed)
    {
        Translate(-right * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_D) == rfe::Pressed)
    {
        Translate(right * deltaTime * speed);
    }
}

void rfe::Camera::ProcessMouseInput(rfe::MouseData mouseData, float deltaTime, float sensitivity) {

    if (!firstMove) {
        lastMouseData.xPos = mouseData.xPos;
        lastMouseData.yPos = mouseData.yPos;
        firstMove = true;
    }

    float xoffset = mouseData.xPos - lastMouseData.xPos;
    float yoffset = lastMouseData.yPos - mouseData.yPos;
    lastMouseData.xPos = mouseData.xPos;
    lastMouseData.yPos = mouseData.yPos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    RecalculateBasisVectors();
}

void rfe::Camera::SetCursorFPS(rfe::Window& window) {
    glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void rfe::Camera::RecalculateBasisVectors() {
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
}
