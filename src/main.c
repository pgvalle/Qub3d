#define GLAD_GL_IMPLEMENTATION
#include <glad.h>
#undef GLAD_GL_IMPLEMENTATION
#include <GLFW/glfw3.h>

#include <assert.h>
#include <stdio.h>

#include "camera.h"
#include "input/mouse.h"
#include "opengl/shader.h"

const char* vert_src = "\
#version 330 core \n\
layout (location = 0) in vec3 aPos; \
uniform mat4 proj; \
uniform mat4 view; \
void main() { \
    gl_Position = proj * view * vec4(aPos.x, aPos.y, aPos.z, 1.0); \
} \
";

const char* frag_src = "\
#version 330 core \n\
out vec4 FragColor; \
void main() { \
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
} \
";

void resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void qub3d_mouse_position_callback(GLFWwindow*, double, double);
void qub3d_mouse_button_callback(GLFWwindow*, int, int, int);
void qub3d_mouse_enter_callback(GLFWwindow*, int);

void qub3d_key_callback(GLFWwindow*, int, int, int, int);

int main()
{
    assert(glfwInit());

    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 450, "Qub3d", NULL, NULL);

    glfwMakeContextCurrent(window);
    assert(gladLoadGL(glfwGetProcAddress));

    glfwSetWindowSizeLimits(window, 400, 225, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // to test camera now

    glfwSetFramebufferSizeCallback(window, resize_callback);

    glfwSetCursorPosCallback(window, qub3d_mouse_position_callback);
    glfwSetMouseButtonCallback(window, qub3d_mouse_button_callback);
    glfwSetCursorEnterCallback(window, qub3d_mouse_enter_callback);

    glfwSetKeyCallback(window, qub3d_key_callback);

    GLuint shader = qub3d_build_shader(vert_src, frag_src, "01");
    glUseProgram(shader);

    float vertices[] = {
         0.5f,  0.5f, -10.0f, // top right
         0.5f, -0.5f, -10.0f, // bottom right
        -0.5f, -0.5f, -10.0f, // bottom left
        -0.5f,  0.5f, -10.0f, // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    qub3d_camera_t cam;
    qub3d_init_camera(&cam);

    mat4x4 proj;
    mat4x4_perspective(proj, 45, 1.7778, 1, 100);
    qub3d_set_shader_mat4(shader, "view", &cam.view[0][0]);
    qub3d_set_shader_mat4(shader, "proj", &proj[0][0]);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        int xvel = qub3d_key(GLFW_KEY_W) - qub3d_key(GLFW_KEY_S);
        int yvel = qub3d_key(GLFW_KEY_SPACE) - qub3d_key(GLFW_KEY_Q);
        int zvel = qub3d_key(GLFW_KEY_D) - qub3d_key(GLFW_KEY_A);
        qub3d_move_camera(&cam, 0.01f * xvel, 0.01f * yvel, 0.01f * zvel);

        if (qub3d_mouse_moving())
        {
            int yaw_offset, pitch_offset;
            qub3d_get_mouse_offset(&yaw_offset, &pitch_offset);
            qub3d_rotate_camera(&cam, yaw_offset, pitch_offset);

            printf("%d %d\n", yaw_offset, pitch_offset);
        }

        qub3d_set_shader_mat4(shader, "view", &cam.view[0][0]);
        qub3d_refresh_mouse();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader);

    glfwTerminate();

    return 0;
}
