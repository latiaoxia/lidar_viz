#include <functional>
#include <iostream>

#include <asio.hpp>
#include "glrender.hpp"

int main(void)
{
    asio::io_context io;

    GlRender render("lidar test");
    render.init();
    int period = 33;
    bool exit = false;

    asio::signal_set signals(io, SIGINT, SIGTERM);
    asio::steady_timer t(io, asio::chrono::milliseconds(period));

    std::function<void (const asio::error_code &)> func = 
        [&](const asio::error_code &err)
        {
            if (render.shouldStop() || exit) {
                std::cout << "close" << std::endl;
                signals.cancel();
                return;
            }
            render.update();
            t.expires_after(asio::chrono::milliseconds(period));
            t.async_wait(func);
        };

    signals.async_wait([&](const asio::error_code&, int)
        {
            std::cout << "exit!" << std::endl;
            exit = true;
        });
    t.async_wait(func);

    io.run();
    // while (!render.shouldStop()) {
        // render.update();
    // }
    return 0;
}

