cmake_minimum_required(VERSION 3.10)

project(Qub3d)

add_compile_definitions("QUB3D_DEBUG=$<CONFIG:Debug>")

# adding all source files
file(GLOB_RECURSE QUB3D_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(qub3d ${QUB3D_SOURCE_FILES})
set_property(TARGET qub3d PROPERTY CXX_STANDARD 11)
set_property(TARGET qub3d PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(qub3d PRIVATE "${CMAKE_SOURCE_DIR}/ext")
target_include_directories(qub3d PRIVATE "${CMAKE_SOURCE_DIR}/src")

set(BUILD_SHARED_LIBS   OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS    OFF)
set(GLFW_BUILD_DOCS     OFF)

add_subdirectory(ext/glfw)
add_dependencies(qub3d glfw)

target_include_directories(qub3d PRIVATE "${glfw_SOURCE_DIR}/include")

target_link_libraries(qub3d PRIVATE glfw)
