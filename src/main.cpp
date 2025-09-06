#include <SDL3/SDL.h>
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "util.hpp"

auto main() -> int {
    try {
        fmt::println("I'M {}", "BATMAN");
        spdlog::error("HE{}", "HE");
        ensure_true(not SDL_Init(SDL_INIT_VIDEO));
    }

    catch(const std::exception &ex) {
        spdlog::error(ex.what());
    }

    catch(...) {
        spdlog::error("Unexpected error.");
    }
}
