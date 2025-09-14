#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>
#include <cstdint>

class EventSystem {
  public:
    using Handler = std::function<void(const SDL_Event &)>;

  public:
    auto registerHandler(std::uint32_t type, Handler handler) -> void {
        m_handlers[type] = std::move(handler);
    }

    auto dispatch(const SDL_Event &event) -> void {
        if(m_handlers.contains(event.type)) {
            m_handlers[event.type](event);
        }
    }

    auto pollEvents() -> void {
        auto event = SDL_Event{};
        while(SDL_PollEvent(&event)) {
            dispatch(event);
        }
    }

  private:
    std::unordered_map<std::uint32_t, Handler> m_handlers;
};
