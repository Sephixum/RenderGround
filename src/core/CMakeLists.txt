add_library(
    core STATIC
    Application.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(core PUBLIC glad spdlog::spdlog)
