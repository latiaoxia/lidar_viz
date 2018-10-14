#ifndef GLRENDER_HPP
#define GLRENDER_HPP

#include <string>

class GLFWwindow;
class Shader;
class GlCamera;

class GlRender {
public:
    GlRender(const std::string &);
    virtual ~GlRender();

    virtual int init();
    virtual void render();
    virtual void resize();

private:
    void mouseButtonCallback(GLFWwindow* window, int button,
                             int action, int mods);
    void 
    GLFWwindow *window = nullptr;
    std::string title;
    int width = 640;
    int height = 480;

    unsigned int vbo, vao, ebo;
    Shader *shader = nullptr;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool isMousePressed = false;

    GlCamera *glCamera = nullptr;
};
#endif
