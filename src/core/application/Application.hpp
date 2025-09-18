#pragma once
#include <SDL3/SDL.h>
#include "../window/Window.hpp"

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

    Window m_window{Window::builder()             //
                        .setTitle("RenderGround") //
                        .setSize(1280, 720)       //
                        .build()};
};
