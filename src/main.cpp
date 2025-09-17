#include <SDL3/SDL.h>
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "core/window/Window.hpp"
#include <glad/glad.h>

auto main() -> int {
    try {
        auto window = Window::builder().setSize(800, 600).setTitle("This Window Is BATMAN").build();

        // window.enableVsync(true);

        window.registerCallbackForSDLEvent(SDL_EVENT_QUIT, [&window](...) { window.close(); });

        while(window.isRunning()) {
            window.pollEvents();
            glClear(GL_COLOR_BUFFER_BIT);
            window.swapBuffers();
        }
    }

    catch(const std::exception &ex) {
        spdlog::error(ex.what());
    }

    catch(...) {
        spdlog::error("Unexpected error.");
    }
}
