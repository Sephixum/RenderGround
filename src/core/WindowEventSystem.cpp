#include "WindowEventSystem.hpp"

auto WindowEventSystem::registerHandler(SDL_EventType type, Handler handler) -> void {
    m_handlers[type] = std::move(handler);
}

auto WindowEventSystem::pollEvents() -> void {
    auto event = SDL_Event{};
    while(SDL_PollEvent(&event)) {
        _dispatch(event);
    }
}

auto WindowEventSystem::_dispatch(const SDL_Event &event) -> void {
    auto sdl_event_type = static_cast<SDL_EventType>(event.type);
    if(m_handlers.contains(sdl_event_type)) {
        m_handlers[sdl_event_type](event);
    }
}
