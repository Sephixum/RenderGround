add_library(
    core STATIC
    Application.cpp
)

target_link_libraries(core PUBLIC ${DEPENDENCIES})
