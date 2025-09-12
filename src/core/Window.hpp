#pragma once

#include <SDL3/SDL.h>

class Window final {
  public:
    class Builder;

  public:
    static auto builder() -> Builder;

  private:
    Window();
    Window(const Window &) = delete("Copying constructing a window is unreasonable.");
    auto operator=(const Window &) -> Window & = delete("Copy assigning a window is unreasonable.");
    Window(Window &&) = default;
    auto operator=(Window &&) -> Window & = default;
    ~Window();

    SDL_Window *m_window = nullptr;
};

// Change to builder pattern
class Window::Builder {};
