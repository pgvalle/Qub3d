cmake_minimum_required(VERSION 3.22)

project(Qub3d)

add_compile_definitions("QUB3D_DEBUG=$<CONFIG:Debug>")

# adding all source files
file(GLOB_RECURSE QUB3D_SOURCE_FILES source/*.cpp)
add_executable(qub3d ${QUB3D_SOURCE_FILES})

set_target_properties(qub3d PROPERTIES
  CXX_STANDARD          11
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS        FALSE
)

target_include_directories(qub3d PRIVATE
  C:/CCppDev/GLFW/include external source)

target_link_libraries(qub3d PRIVATE C:/CCppDev/GLFW/lib-static-ucrt/glfw3dll.lib)
