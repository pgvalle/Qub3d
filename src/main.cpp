#include <glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <assert.h>
#include <stdio.h>

#include "camera.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "chunk.h"
#include "opengl/shader.h"

// CALLBACK DECLARATIONS (definitions in mouse.cpp and keyboard.cpp)

void resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void qub3d_mouse_position_callback(GLFWwindow*, double, double);
void qub3d_mouse_button_callback(GLFWwindow*, int, int, int);
void qub3d_mouse_enter_callback(GLFWwindow*, int);
void qub3d_key_callback(GLFWwindow*, int, int, int, int);

static GLFWwindow* qub3d_window = NULL;

const char* vert_src = R"SHADER(
#version 330 core
layout (location = 0) in vec3 position;

out vec2 uvs;

uniform mat4 proj;
uniform mat4 view;

void main() {
    gl_Position = proj * view * vec4(position, 1.0);
}
)SHADER";

const char* frag_src = R"SHADER(
#version 330 core

in  vec2 uvs;
out vec4 FragColor;

void main() {
    FragColor = vec4(1, 0.4, 0.8, 1);
}
)SHADER";

void configure_glfw()
{
    assert(glfwInit());

    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    qub3d_window = glfwCreateWindow(800, 450, "Qub3d", NULL, NULL);
    glfwMakeContextCurrent(qub3d_window);
    assert(gladLoadGL(glfwGetProcAddress));

    glfwSetWindowSizeLimits(qub3d_window, 400, 225, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(qub3d_window, resize_callback);
    glfwSetCursorPosCallback(qub3d_window, qub3d_mouse_position_callback);
    glfwSetMouseButtonCallback(qub3d_window, qub3d_mouse_button_callback);
    glfwSetCursorEnterCallback(qub3d_window, qub3d_mouse_enter_callback);
    glfwSetKeyCallback(qub3d_window, qub3d_key_callback);

    glfwSwapInterval(1);
}

int main()
{
    configure_glfw();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_CW);

    // bottom left, bottom-right, top-right, top-left
    vec3 vertices[] = {
          0.5f, -0.5f, -20.f,
          0.5f,  0.5f, -20.f,
         -0.5f,  0.5f, -20.f,
         -0.5f, -0.5f, -20.f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    qub3d_chunk* chunk = qub3d_generate_chunk();
    qub3d_chunk_mesh mesh = qub3d_build_chunk_mesh(*chunk);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * mesh.len_vertices, mesh.vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * mesh.len_indices, mesh.indices, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    qub3d_camera cam;

    GLuint shader = qub3d_build_shader(vert_src, frag_src, "01");
    glUseProgram(shader);

    mat4x4 proj;
    mat4x4_perspective(proj, 45, 1.7778f, 1, 100);
    qub3d_set_shader_mat4(shader, "view", cam.get_view_mat());
    qub3d_set_shader_mat4(shader, "proj", proj);

    int use_camera = 0;

    while (!glfwWindowShouldClose(qub3d_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, mesh.len_indices, GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(qub3d_window);
        glfwPollEvents();

        if (use_camera)
        {
            int xvel = qub3d_key(GLFW_KEY_W) - qub3d_key(GLFW_KEY_S);
            int yvel = qub3d_key(GLFW_KEY_SPACE) - qub3d_key(GLFW_KEY_LEFT_SHIFT);
            int zvel = qub3d_key(GLFW_KEY_D) - qub3d_key(GLFW_KEY_A);
            cam.move(0.1f * xvel, 0.1f * yvel, 0.1f * zvel);

            if (qub3d_mouse_moving())
            {
                int yaw_offset, pitch_offset;
                qub3d_get_mouse_offset(&yaw_offset, &pitch_offset);
                cam.rotate(1.0f * yaw_offset, 1.0f * pitch_offset);
            }

            qub3d_set_shader_mat4(shader, "view", cam.get_view_mat());

            if (qub3d_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                use_camera = 0;
                glfwSetInputMode(qub3d_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        else if (qub3d_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            use_camera = 1;
            glfwSetInputMode(qub3d_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        qub3d_refresh_mouse();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader);

    glfwDestroyWindow(qub3d_window);
    glfwTerminate();

    return 0;
}
