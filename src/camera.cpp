#include "camera.hpp"

Camera::Camera(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch) :
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    moveSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM)
{
    position = _position;
    worldUp = _up;
    yaw = _yaw;
    pitch = _pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ,
               float upX, float upY, float upZ,
               float _yaw, float _pitch) :
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    moveSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM)
{
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    yaw = _yaw;
    pitch = _pitch;
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = _front;

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
