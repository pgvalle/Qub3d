cmake_minimum_required(VERSION 3.22)

project(unblock3d)

# adding executable and all source files
file(GLOB_RECURSE unblock3d_SOURCE_FILES source/*.cpp)
add_executable(unblock3d ${unblock3d_SOURCE_FILES})

# std::filesystem is used and it requires at least c++20
set_target_properties(unblock3d PROPERTIES
  CXX_STANDARD          20
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS        FALSE
)

target_include_directories(unblock3d PRIVATE source/ external/)


message(STATUS "Setting up GLFW")

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.3.9
)

set(BUILD_SHARED_LIBS   OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS    OFF)
set(GLFW_BUILD_DOCS     OFF)
FetchContent_MakeAvailable(glfw)

add_dependencies(unblock3d glfw)
target_include_directories(unblock3d PRIVATE ${glfw3_INCLUDE_DIRS})
target_link_libraries(unblock3d PRIVATE glfw)


message(STATUS "Setting up GLM")

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

add_dependencies(unblock3d glm)
target_include_directories(unblock3d PRIVATE glm)
target_link_libraries(unblock3d PRIVATE glm)
