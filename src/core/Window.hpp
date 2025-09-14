#pragma once

#include "WindowEventSystem.hpp"
#include <SDL3/SDL.h>
#include <cstdint>
#include <string_view>
#include <memory>
#include <functional>

namespace detail {

    struct SDLWindowDestructor {
        static auto operator()(SDL_Window *window_ptr) -> void { SDL_DestroyWindow(window_ptr); }
    };

    struct SDLOpenGLContextDestructor {
        static auto operator()(SDL_GLContext gl_context) {};
    };

} // namespace detail

using SDLWindow = std::unique_ptr<SDL_Window, detail::SDLWindowDestructor>;

class SDLOpenGLContext {
  public:
    SDLOpenGLContext(const SDLWindow &associated_window)
        : m_sdl_context{SDL_GL_CreateContext(associated_window.get())} {}

  private:
    SDL_GLContext m_sdl_context = nullptr;
};

class Window final {
  public:
    class Builder;

  public:
    static auto builder() -> Builder;

  public:
    auto swapBuffers() -> void;
    auto makeCurrent() -> void;
    auto registerCallbackForSDLEvent(SDL_EventType type, WindowEventSystem::Handler func) -> void;
    auto pollEvents() -> void;
    auto enableVsync(bool value) -> void;

  private:
    Window(Builder &&builder);
    Window(const Window &) = delete("Copying constructing a window is unreasonable.");
    auto operator=(const Window &) -> Window & = delete("Copy assigning a window is unreasonable.");
    Window(Window &&) = default;
    auto operator=(Window &&) -> Window & = default;
    ~Window();

    SDLWindow m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    WindowEventSystem m_event_system = {};
};

class Window::Builder final {
    using Self = Window::Builder;

  public:
    auto setSize(this Self &&self, std::uint32_t width, std::uint32_t height) -> Self &&;
    auto setTitle(this Self &&self, std::string_view title) -> Self &&;
    auto setResizeable(this Self &&self, bool value) -> Self &&;
    auto setFullscreen(this Self &&self, bool value) -> Self &&;
    auto setBorderless(this Self &&self, bool value) -> Self &&;

    auto build(this Self &&self) -> Window { return {std::move(self)}; }

  private:
    std::string m_title = "SDL3 Window";
    std::uint32_t m_width = 800;
    std::uint32_t m_height = 600;
    bool m_resizable = true;
    bool m_fullscreen = false;
    bool m_borderless = false;

    friend class Window;
};
