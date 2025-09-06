#pragma once

class Application {
  public:
    static auto getInstance() -> Application &;

  private:
    Application() = default;
    Application(const Application &other) = delete;
    Application(Application &&other) = delete;
    auto operator=(const Application &other) -> Application & = delete;
    auto operator=(Application &&other) -> Application & = delete;
};
