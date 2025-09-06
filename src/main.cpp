#include "core/Application.hpp"
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

auto main() -> int {
    try {
        // fmt::println("I'M {}", "BATMAN");
        // spdlog::error("HE{}", "HE");
        // ensure_true(not SDL_Init(SDL_INIT_VIDEO));
        Application::getInstance();
    }

    catch (const std::exception &ex) {
        spdlog::error(ex.what());
    }

    catch (...) {
        spdlog::error("Unexpected error.");
    }
}
