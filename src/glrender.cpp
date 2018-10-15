#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glrender.hpp"
#include "glcamera.hpp"
#include "shader.hpp"

GlRender::GlRender(const std::string &_title)
{
    title = _title;
    glCamera = new GlCamera(glm::vec3(0.0f, 0.0f, 1.0f));
}

GlRender::~GlRender()
{
    delete shader;
    delete glCamera;

    glfwTerminate();
}

int GlRender::init()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glfwSetWindowUserPointer(window, this);
    auto buttonFunc = [](GLFWwindow *w, int b, int a, int m)
    {
        static_cast<GlRender*>(glfwGetWindowUserPointer(w))
            ->mouseButtonCallback(w, b, a, m);
    };
    glfwSetMouseButtonCallback(window, buttonFunc);

    auto moveFunc = [](GLFWwindow* w, double x, double y)
    {
        static_cast<GlRender*>(glfwGetWindowUserPointer(w))
            ->mouseMoveCallback(w, x, y);
    };
    glfwSetCursorPosCallback(window, moveFunc);

    auto scrollFunc = [](GLFWwindow* w, double x, double y)
    {
        static_cast<GlRender*>(glfwGetWindowUserPointer(w))
            ->mouseScrollCallback(w, x, y);
    };
    glfwSetScrollCallback(window, scrollFunc);

    // auto keyFunc = [](GLFWwindow *w, int k, int s, int a, int m)
    // {
        // static_cast<GlRender*>(glfwGetWindowUserPointer(w))
            // ->keyCallback(w, k, s, a, m);
    // };
    // glfwSetKeyCallback(window, keyFunc);
        
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    std::ifstream infile("0000000000.txt");
    std::string line;
    glm::vec3 point;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (!(iss >> point.x >> point.y >> point.z)) {
            std::cout << "error" << std::endl;
            break;
        }

        point /= 1.0;
        pointsBuffer.push_back(point);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, pointsBuffer.size() * sizeof(glm::vec3),
                 pointsBuffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader = new Shader("vshader.vsh", "fshader.fsh");
}

void GlRender::update()
{
    glfwMakeContextCurrent(window);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processKeyboard();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    glm::mat4 projection = glm::perspective(glm::radians(glCamera->zoom),
                                            (float)width / height,
                                            near, far);
    shader->setMat4("projection", projection);

    glm::mat4 view = glCamera->getViewMatrix();
    shader->setMat4("view", view);

    glm::mat4 model(1.0);
    shader->setMat4("model", model);

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, pointsBuffer.size());

    glfwSwapBuffers(window);
    
    glfwPollEvents();
}

void GlRender::resize()
{
}
void GlRender::mouseButtonCallback(GLFWwindow* window, int button,
                                   int action, int mods)
{
    if (action == GLFW_PRESS) {
        double xpos, ypos;

        isMousePressed = true;
        glfwGetCursorPos(window, &xpos, &ypos);
        lastX = (float)xpos;
        lastY = (float)ypos;
    } else {
        isMousePressed = false;
    }
}

void GlRender::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (isMousePressed == false)
        return;
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    glCamera->processMouseMovement(xoffset, yoffset);
}

void GlRender::mouseScrollCallback(GLFWwindow* window,
                                   double xoffset, double yoffset)
{
    glCamera->processMouseScroll((float)yoffset);
}

void GlRender::keyCallback(GLFWwindow *window, int key, int scancode,
                           int action, int mods)
{
    static int a = 0;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_W :
            glCamera->processKeyboard(GlCamera::FORWARD, deltaTime);
            break;
        case GLFW_KEY_S :
            glCamera->processKeyboard(GlCamera::BACKWARD, deltaTime);
            break;
        case GLFW_KEY_A :
            glCamera->processKeyboard(GlCamera::LEFT, deltaTime);
            break;
        case GLFW_KEY_D :
            glCamera->processKeyboard(GlCamera::RIGHT, deltaTime);
            break;
        case GLFW_KEY_ESCAPE :
            glfwSetWindowShouldClose(window, true);
            m_shouldStop = true;
            break;
        default:
            break;
        }
    }
}

void GlRender::processKeyboard()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        m_shouldStop = true;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glCamera->processKeyboard(GlCamera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glCamera->processKeyboard(GlCamera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glCamera->processKeyboard(GlCamera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glCamera->processKeyboard(GlCamera::RIGHT, deltaTime);
}

