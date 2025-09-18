add_library(
    core_application STATIC
    Application.cpp
)

target_link_libraries(core_application PUBLIC ${DEPENDENCIES})
