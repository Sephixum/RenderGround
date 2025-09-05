cmake_minimum_required(VERSION 3.21)

# Set standard if it is not used by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

# Export build database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  our_project
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES CXX C
)

add_executable(${PROJECT_NAME})

include(Dependencies.cmake)
include(CompilerWarnings.cmake)

# Get the dependencies into a list
project_setup_dependencies(DEPENDENCIES)
message(STATUS "Deps collected: ${DEPENDENCIES}")
project_setup_compiler_warnings()

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_${CMAKE_CXX_STANDARD})

# Link against the collected deps
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDENCIES})
