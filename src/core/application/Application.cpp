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
    ensure_true(SDL_Init(SDL_INIT_VIDEO));

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    m_window = SDL_CreateWindow(config::WINDOW_TITLE,
                                config::WINDOW_WIDTH,
                                config::WINDOW_HEIGHT,
                                SDL_WINDOW_OPENGL);
    ensure_true(m_window != nullptr);

    m_glContext = SDL_GL_CreateContext(m_window);
    ensure_true(m_glContext != nullptr);

    ensure_true(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress));
}

Application::Application() { init(); }
