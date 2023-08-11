cmake_minimum_required(VERSION 3.10)

project(Qub3d)

add_compile_definitions("QUB3D_DEBUG=$<CONFIG:Debug>")

# adding all source files
file(GLOB_RECURSE QUB3D_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c)
add_executable(qub3d ${QUB3D_SOURCE_FILES})
set_property(TARGET qub3d PROPERTY C_STANDARD 99)

target_include_directories(qub3d PRIVATE ${CMAKE_SOURCE_DIR}/ext)
target_include_directories(qub3d PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(ext/glfw)
add_dependencies(qub3d glfw)

set(BUILD_SHARED_LIBS   OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS    OFF)
set(GLFW_BUILD_DOCS     OFF)

target_include_directories(qub3d PRIVATE ${glfw_SOURCE_DIR}/include)

target_link_libraries(qub3d PRIVATE glfw)
