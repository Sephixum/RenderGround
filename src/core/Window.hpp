#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <string_view>
#include <memory>

namespace detail {
    struct SDLWindowDestructor {
        static auto operator()(SDL_Window *window_ptr) -> void { SDL_DestroyWindow(window_ptr); }
    };
} // namespace detail

using SDLWindow = std::unique_ptr<SDL_Window, detail::SDLWindowDestructor>;

class Window final {
  public:
    class Builder;

  public:
    static auto builder() -> Builder;

  private:
    Window(Builder &&builder);
    Window(const Window &) = delete("Copying constructing a window is unreasonable.");
    auto operator=(const Window &) -> Window & = delete("Copy assigning a window is unreasonable.");
    Window(Window &&) = default;
    auto operator=(Window &&) -> Window & = default;
    ~Window();

    SDLWindow m_window = nullptr;
    SDL_GLContext m_context = nullptr;
};

class Window::Builder final {
    using Self = Window::Builder;

  public:
    auto setSize(this Self &&self, std::uint32_t width, std::uint32_t height) -> Self &&;
    auto setTitle(this Self &&self, std::string_view title) -> Self &&;
    auto resizeable(this Self &&self, bool value) -> Self &&;
    auto fullscreen(this Self &&self, bool value) -> Self &&;
    auto borderless(this Self &&self, bool value) -> Self &&;

  private:
    std::string m_title = "SDL3 Window";
    std::uint32_t m_width = 800;
    std::uint32_t m_height = 600;
    bool m_resizable = true;
    bool m_fullscreen = false;
    bool m_borderless = false;

    friend class Window;
};
