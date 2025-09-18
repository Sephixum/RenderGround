#include <SDL3/SDL.h>
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

auto main() -> int {
    try {
        spdlog::info("WINDOW IS BATMAN");
    }

    catch(const std::exception &ex) {
        spdlog::error(ex.what());
    }

    catch(...) {
        spdlog::error("Unexpected error.");
    }
}
