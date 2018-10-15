#ifndef GLRENDER_HPP
#define GLRENDER_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

class GLFWwindow;
class Shader;
class GlCamera;

class GlRender {
public:
    GlRender(const std::string &);
    virtual ~GlRender();

    virtual int init();
    virtual void update();
    virtual void resize();

    bool shouldStop();

private:
    void mouseButtonCallback(GLFWwindow* window, int button,
                             int action, int mods);
    void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void keyCallback(GLFWwindow *window, int key, int scancode,
                     int action, int mods);
    void processKeyboard();

    GLFWwindow *window = nullptr;
    std::string title;
    int width = 640;
    int height = 480;
    bool isMousePressed = false;
    float lastX = width / 2.0f;
    float lastY = height / 2.0f;
    bool m_shouldStop = false;

    unsigned int vbo, vao, ebo;
    Shader *shader = nullptr;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    std::vector<glm::vec3> pointsBuffer;

    GlCamera *glCamera = nullptr;
    float near = 0.1, far = 100.0;
};

inline bool GlRender::shouldStop()
{
        return m_shouldStop;
}
#endif
