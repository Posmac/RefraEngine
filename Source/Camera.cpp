#include "Camera.h"

rfe::Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float speed,
                    float yaw, float pitch, float roll)
    : position(position), forward(forward), up(up),
    yaw(yaw), pitch(pitch), roll(roll), speed(speed)
{
}

void rfe::Camera::Translate(const glm::vec3 &newPosition)
{
    position += newPosition;
}

glm::mat4 rfe::Camera::DynamicViewMatrix()
{
    glm::vec3 zaxis = glm::normalize(forward); //forward vector
    glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis)); // right vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis); // up vector

    glm::mat4 viewMatrix = {
            glm::vec4(          xaxis.x,                        yaxis.x,                        zaxis.x,              0),
            glm::vec4(          xaxis.y,                        yaxis.y,                        zaxis.y,              0),
            glm::vec4(          xaxis.z,                        yaxis.z,                        zaxis.z,              0),
            glm::vec4( -glm::dot(xaxis, position),-glm::dot(yaxis, position) ,-glm::dot(zaxis, position),1),
    };

    return viewMatrix;
}

glm::mat4 rfe::Camera::StaticViewMatrix(const glm::vec3 targetPosition)
{
    glm::vec3 zaxis = glm::normalize(position - targetPosition); //forward vector
    glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis)); // right vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis); // up vector

    glm::mat4 viewMatrix = {
            glm::vec4(          xaxis.x,                        yaxis.x,                        zaxis.x,              0),
            glm::vec4(          xaxis.y,                        yaxis.y,                        zaxis.y,              0),
            glm::vec4(          xaxis.z,                        yaxis.z,                        zaxis.z,              0),
            glm::vec4( -glm::dot(xaxis, position),-glm::dot(yaxis, position) ,-glm::dot(zaxis, position),1),
            };

    return viewMatrix;
}

glm::mat4 rfe::Camera::ProjectionMatrix()
{
    return glm::mat4();
}

void rfe::Camera::ProcessInput(rfe::Input& input, float deltaTime) {
    if(input.GetKeyState(rfe::KEY_W) == rfe::Pressed)
    {
        Translate(-forward * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_S) == rfe::Pressed)
    {
        Translate(forward * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_A) == rfe::Pressed)
    {
        Translate(-glm::normalize(glm::cross(up, forward)) * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_D) == rfe::Pressed)
    {
        Translate(glm::normalize(glm::cross(up, forward)) * deltaTime * speed);
    }
    if(input.GetKeyState(rfe::KEY_R) == rfe::Released)
    {
        position = glm::vec3(0, 0, 5);
    }
}
