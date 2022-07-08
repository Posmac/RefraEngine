#include "Camera.h"

rfe::Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float speed,
                    float yaw, float pitch, float roll)
    : position(position), forward(forward), up(up),
    yaw(yaw), pitch(pitch), roll(roll), speed(speed)
{
    lastMouseData.xPos = 1280/2;
    lastMouseData.yPos = 720/2;
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

glm::mat4 rfe::Camera::ProjectionMatrix(ProjectionType projectionType)
{
    glm::mat4 projectionMatrix;
    if(projectionType == rfe::Perspective)
    {

    }
    else
    {

    }

    return projectionMatrix;
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
        Translate(glm::normalize(glm::cross(up, forward)) * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_D) == rfe::Pressed)
    {
        Translate(-glm::normalize(glm::cross(up, forward)) * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_R) == rfe::Released)
    {
        position = glm::vec3(0, 0, 5);
    }
}

void rfe::Camera::ProcessMouseInput(rfe::MouseData mouseData, float deltaTime, float sensitivity) {
    if(!firstMove)
    {
        mouseData.xPos = lastMouseData.xPos;
        mouseData.yPos = lastMouseData.yPos;
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

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    right = glm::normalize(glm::cross(up, direction));
    up = glm::normalize(glm::cross(right, direction));
    std::cout << direction.x  << "  "  << direction.y << "  " << direction.z << std::endl;

    forward = glm::normalize(direction);
}

void rfe::Camera::SetCursorFPS(rfe::Window& window) {
    glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
