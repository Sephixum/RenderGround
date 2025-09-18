#include "core/application/Application.hpp"
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

auto main() -> int {
    try {
        Application::getInstance().run();
    }

    catch(const std::exception &ex) {
        spdlog::error(ex.what());
    }

    catch(...) {
        spdlog::error("Unexpected error.");
    }
}
