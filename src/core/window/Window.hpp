#pragma once

#include "WindowEventSystem.hpp"
#include <SDL3/SDL.h>
#include <cstdint>
#include <string_view>
#include <memory>
#include <functional>

namespace detail {

    struct SDLWindowDestructor {
        inline static auto operator()(SDL_Window *window_ptr) -> void {
            SDL_DestroyWindow(window_ptr);
        }
    };

    struct SDLOpenGLContextDestructor {
        inline static auto operator()(SDL_GLContextState *gl_context) -> void {
            SDL_GL_DestroyContext(gl_context);
        };
    };

} // namespace detail

class Window final {
  private:
    using SDLWindow = std::unique_ptr< //
        SDL_Window,                    //
        detail::SDLWindowDestructor    //
        >;

    using SDLOpenGLContext = std::unique_ptr< //
        SDL_GLContextState,                   //
        detail::SDLOpenGLContextDestructor    //
        >;

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
    auto isRunning() -> bool;
    auto close() -> void;

    ~Window() = default;

  private:
    Window(Builder &&builder);
    Window(const Window &) = delete;
    auto operator=(const Window &) -> Window & = delete;
    Window(Window &&) = default;
    auto operator=(Window &&) -> Window & = default;

  private:
    bool m_running = true;

    SDLWindow m_window = nullptr;
    SDLOpenGLContext m_context = nullptr;

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
