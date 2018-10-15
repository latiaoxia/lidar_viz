#include <asio.hpp>
#include "glrender.hpp"

int main(void)
{
    GlRender render("lidar test");
    render.init();

    while (!render.shouldStop()) {
        render.update();
    }
    return 0;
}

