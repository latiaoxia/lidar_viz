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
        
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // load lidar points
    std::vector<glm::vec3> verts;

    std::ifstream infile("0000000000.txt");
    std::string line;
    glm::vec3 point;
    // for (int i = 0; i < 300; i++) {
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        if (!(iss >> point.x >> point.y >> point.z)) {
            std::cout << "error" << std::endl;
            break;
        }

        point /= 1.0;
        verts.push_back(point);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3),
                 verts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader = new Shader("vshader.vsh", "fshader.fsh");
}

void GlRender::render()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    glm::mat4 projection = glm::perspective(glm::ra
}

void GlRender::resize()
{
}
