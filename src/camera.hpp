#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float ROLL         = 0.0f;
const float PITCH       =  -89.0f;
const float SPEED       =  8.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // Euler Angles
    float roll;
    float pitch;
    // Camera options
    float moveSpeed;
    float mouseSensitivity;
    float zoom;

    // Constructor with vectors
    Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 _up = glm::vec3(0.0f, 0.0f, 1.0f),
           float _roll = ROLL, float pitch = PITCH);
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float roll, float pitch);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Camera_Movement direction, float deltaTime);

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset,
                              bool constrainpitch = true);

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void processMouseScroll(float yoffset);

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};
#endif
