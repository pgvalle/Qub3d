cmake_minimum_required(VERSION 3.10)

project(Qub3d)

add_compile_definitions("QUB3D_DEBUG=$<CONFIG:Debug>")

# adding all source files
file(GLOB_RECURSE QUB3D_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c)
add_executable(qub3d ${QUB3D_SOURCE_FILES})
set_property(TARGET qub3d PROPERTY C_STANDARD 99)

target_include_directories(qub3d PRIVATE ${CMAKE_SOURCE_DIR}/ext)
target_include_directories(qub3d PRIVATE ${CMAKE_SOURCE_DIR}/src)

find_package(glfw 3.3 QUIET)
if(NOT glfw_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.8
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/glfw
    )
    # pre-configuration and download
    set(BUILD_SHARED_LIBS   OFF)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS    OFF)
    set(GLFW_BUILD_DOCS     OFF)
    FetchContent_MakeAvailable(glfw)

    # integration
    target_include_directories(qub3d PRIVATE ${glfw_SOURCE_DIR}/include)
endif()

# integration
add_dependencies(qub3d glfw)
target_link_libraries(qub3d PRIVATE glfw)
