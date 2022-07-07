#include "Camera.h"

rfe::Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up,
                    float yaw, float pitch, float roll)
    : position(position), forward(forward), up(up),
    yaw(yaw), pitch(pitch), roll(roll)
{
}

void rfe::Camera::Translate(const glm::vec3 &newPosition)
{

}

glm::mat4 rfe::Camera::DynamicViewMatrix()
{
    return {};
}

glm::mat4 rfe::Camera::StaticViewMatrix(const glm::vec3 targetPosition)
{
    glm::vec3 zaxis = glm::normalize(position - targetPosition); //forward vector
    glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis)); // right vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis); // up vector

    //not optimized view matrix creation
    /*glm::mat4 orientationMatrix = {
            glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0),
            glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0),
            glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0),
            glm::vec4(  0,       0 ,      0,     1),
            };

    glm::mat4 translation = {
            glm::vec4(    1,           0,           0,       0),
            glm::vec4(    0,           1,           0,       0),
            glm::vec4(    0,           0,           1,       0),
            glm::vec4(-position.x, -position.y, -position.z, 1),
            };*/

    //optimized one
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
