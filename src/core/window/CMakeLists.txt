add_library(
  core_window
  STATIC
  Window.cpp
  WindowEventSystem.cpp
)

target_link_libraries(core_window PUBLIC ${DEPENDENCIES})
