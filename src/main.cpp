#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <fmt/format.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

auto main() -> int {
  fmt::println("I'M {}", "BATMAN");
  spdlog::error("HE{}", "HE");
  SDL_Init(SDL_INIT_VIDEO);
}
