#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>

class WindowEventSystem {
  public:
    using Handler = std::function<void(const SDL_Event &)>;

  public:
    WindowEventSystem() = default;

    auto registerHandlerForEvent(SDL_EventType type, Handler handler) -> void;
    auto pollEvents() -> void;

  private:
    auto _dispatch(const SDL_Event &event) -> void;

    std::unordered_map<SDL_EventType, Handler> m_handlers;
};
