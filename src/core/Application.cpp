#include "Application.hpp"
#include "util.hpp"

auto Application::getInstance() -> Application & {
    local_persist auto *instance = new Application{};
    return *instance;
}
