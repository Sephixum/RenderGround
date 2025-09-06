#pragma once
#include <SDL3/SDL.h>

class Application {
  public:
    static auto getInstance() -> Application &;

    auto run() -> void;

  private:
    Application();
    Application(const Application &other) = delete;
    Application(Application &&other) = delete;
    auto operator=(const Application &other) -> Application & = delete;
    auto operator=(Application &&other) -> Application & = delete;

    auto init() -> void;
    auto handleEvents() -> void;
    auto update(float deltatime) -> void;
    auto render() -> void;

    SDL_Window *m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
};
