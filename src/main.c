#define GLAD_GL_IMPLEMENTATION
#include <glad.h>

#include "app.h"

#include <assert.h>
#include <stdio.h>

// CALLBACK DEFINITION IN app.c!

void mouse_button_callback(GLFWwindow*, int, int, int);
void mouse_motion_callback(GLFWwindow*, double, double);
void mouse_enter_callback(GLFWwindow*, int);

void key_callback(GLFWwindow*, int, int, int, int);

void resize_callback(GLFWwindow*, int, int);

int main()
{
    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    app.window = glfwCreateWindow(400, 225, "Qub3d", NULL, NULL);
    glfwMakeContextCurrent(app.window);

    // setup callbacks
    glfwSetMouseButtonCallback(app.window, mouse_button_callback);
    glfwSetCursorPosCallback(app.window, mouse_motion_callback);
    glfwSetCursorEnterCallback(app.window, mouse_enter_callback);

    glfwSetKeyCallback(app.window, key_callback);

    glfwSetFramebufferSizeCallback(app.window, resize_callback);

    assert(gladLoadGL((GLADloadfunc)glfwGetProcAddress));

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(app.window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
