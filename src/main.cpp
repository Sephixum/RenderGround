#include <SDL3/SDL.h>
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "util.hpp"

auto main() -> int {
    for(auto i : {1, 2, 3}) {
        fmt::println("Hello");
    }

    if(auto res = ensure_true(1 > 2, "1 is not bigger than 2"); not res) {
        spdlog::error(res.error());
    }

    fmt::println("I'M {}", "BATMAN");
    spdlog::error("HE{}", "HE");
    SDL_Init(SDL_INIT_VIDEO);
}
