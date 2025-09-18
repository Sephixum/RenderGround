#include "Application.hpp"
#include "../../config.hpp"
#include "../../util.hpp"
#include <SDL3/SDL_video.h>
#include <glad/glad.h>

auto Application::getInstance() -> Application & {
    local_persist auto *instance = new Application{};
    return *instance;
}

auto Application::init() -> void {
    ensure_true(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress));
}

auto Application::handleEvents() -> void { m_window.pollEvents(); }

auto Application::run() -> void {
    auto last_time = static_cast<float>(SDL_GetTicks());
    while(m_window.isRunning()) {
        auto current_time = static_cast<float>(SDL_GetTicks());
        auto deltatime = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        handleEvents();
        // update(deltatime);
        render();
    }
}

auto Application::render() -> void {
    m_window.makeCurrent();

    glClearColor(0.1f, 0.5f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_window.swapBuffers();
}

Application::Application() { init(); }
