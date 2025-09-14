#include "Window.hpp"
#include "SDL3/SDL_video.h"
#include "util.hpp"

Window::Window(Builder &&builder) {
    SDL_GL_SetAttribute(SDL_GLAttr::SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GLAttr::SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GLAttr::SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GLAttr::SDL_GL_DOUBLEBUFFER, 1);

    ensure_true(SDL_Init(SDL_INIT_VIDEO) == true);

    m_window = SDLWindow{SDL_CreateWindow(builder.m_title.c_str(),
                                          static_cast<int>(builder.m_width),
                                          static_cast<int>(builder.m_height),
                                          [&] {
                                              auto flags = SDL_WindowFlags{};

                                              if(builder.m_resizable)
                                                  flags |= SDL_WINDOW_RESIZABLE;
                                              if(builder.m_fullscreen)
                                                  flags |= SDL_WINDOW_FULLSCREEN;
                                              if(builder.m_borderless)
                                                  flags |= SDL_WINDOW_BORDERLESS;

                                              flags |= SDL_WINDOW_OPENGL;
                                              return flags;
                                          }())};
    ensure_true(m_window != nullptr);
    m_context = SDL_GL_CreateContext(m_window.get());
    ensure_true(m_context != nullptr);
    SDL_GL_MakeCurrent(m_window.get(), m_context);
}

auto Window::swapBuffers() -> void { SDL_GL_SwapWindow(m_window.get()); }

auto Window::makeCurrent() -> void { SDL_GL_MakeCurrent(m_window.get(), m_context); }

auto Window::registerCallbackForSDLEvent(SDL_EventType type, WindowEventSystem::Handler func)
    -> void {
    m_event_system.registerHandler(type, std::move(func));
}

auto Window::pollEvents() -> void { m_event_system.pollEvents(); }

auto Window::enableVsync(bool value) -> void {
    ensure_true(SDL_GL_SetSwapInterval(static_cast<int>(value)) == true);
}

Window::~Window() {
    if(m_context) {
        SDL_GL_DestroyContext(m_context);
        m_context = nullptr;
    }
}

auto Window::Builder::setSize(this Self &&self, std::uint32_t width, std::uint32_t height)
    -> Self && {
    self.m_width = width;
    self.m_height = height;
    return self;
}

auto Window::Builder::setTitle(this Self &&self, std::string_view title) -> Self && {
    self.m_title = title;
    return self;
}

auto Window::Builder::setResizeable(this Self &&self, bool value) -> Self && {
    self.m_resizable = value;
    return self;
}

auto Window::Builder::setFullscreen(this Self &&self, bool value) -> Self && {
    self.m_fullscreen = value;
    return self;
}

auto Window::Builder::setBorderless(this Self &&self, bool value) -> Self && {
    self.m_borderless = value;
    return self;
}
