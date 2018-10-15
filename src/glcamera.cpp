#include "glcamera.hpp"

#include <iostream>

GlCamera::GlCamera(glm::vec3 _position, glm::vec3 _up, float _roll, float _pitch) :
    front(glm::vec3(0.0f, 0.0174524f, -0.999848f)),
    moveSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM)
{
    position = _position;
    worldUp = _up;
    roll = _roll;
    pitch = _pitch;
    updateCameraVectors();
}

GlCamera::GlCamera(float posX, float posY, float posZ,
               float upX, float upY, float upZ,
               float _roll, float _pitch) :
    front(glm::vec3(0.0f, 0.0174524f, -0.999848f)),
    moveSpeed(SPEED),
    mouseSensitivity(SENSITIVITY),
    zoom(ZOOM)
{
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    roll = _roll;
    pitch = _pitch;
    updateCameraVectors();
}

void GlCamera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = moveSpeed * deltaTime;
    switch (direction) {
    case FORWARD:
        position += front * velocity;
        break;
    case BACKWARD:
        position -= front * velocity;
        break;
    case LEFT:
        position -= right * velocity;
        break;
    case RIGHT:
        position += right * velocity;
        break;
    default:
        break;
    }
}

void GlCamera::processMouseMovement(float xoffset, float yoffset,
                                    bool constrainpitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    roll -= xoffset;
    pitch -= yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainpitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update front, right and up Vectors using the updated Euler angles
    updateCameraVectors();
}

void GlCamera::processMouseScroll(float yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void GlCamera::updateCameraVectors()
{
    glm::vec3 _front;
    _front.x = sin(glm::radians(roll)) * cos(glm::radians(pitch));
    _front.y = cos(glm::radians(pitch)) * cos(glm::radians(roll));
    _front.z = sin(glm::radians(pitch));
    front = _front;

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
