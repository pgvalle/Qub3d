#include <glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <initializer_list>

#include <assert.h>
#include <stdio.h>

#include "world/chunk.h"
#include "world/Camera.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "opengl/shader.h"

const char* vert_src = R"SHADER(
#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 uvs;

uniform mat4 proj;
uniform mat4 view;

void main() {
    gl_Position = proj * view * vec4(pos, 1.0);
    uvs = uv;
}
)SHADER";

const char* frag_src = R"SHADER(
#version 330 core

uniform sampler2D tex;

in  vec2 uvs;
out vec4 FragColor;

void main() {
    FragColor = texture(tex, uvs);
}
)SHADER";

static GLFWwindow* window = nullptr;

void configure_glfw()
{
    assert(glfwInit());

    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Qub3d", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    assert(gladLoadGL(glfwGetProcAddress));

    glfwSetWindowSizeLimits(window, 400, 225, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetCursorPosCallback(window, Mouse::pos_callback);
    glfwSetMouseButtonCallback(window, Mouse::button_callback);
    glfwSetCursorEnterCallback(window, Mouse::enter_callback);
    glfwSetKeyCallback(window, Keyboard::key_callback);

    glfwSwapInterval(1);
}

using namespace qub3d;

int main()
{
    configure_glfw();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_CW);

    Chunk chunk;
    chunk.generate();
    ChunkMesh model;
    model.build(chunk);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, model.vertex_buffer_size(), model.vertex_data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.index_buffer_size(), model.index_data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    // texture 1
    // ---------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    int width, height;
    unsigned char* data = stbi_load("dirt.png", &width, &height, NULL, 3);
    assert(data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    Camera cam;

    GLuint shader = qub3d::build_shader(vert_src, frag_src, "01");
    glUseProgram(shader);

    glUniform1i(glGetUniformLocation(shader, "tex"), 0);
    glActiveTexture(GL_TEXTURE0);

    mat4x4 proj;
    mat4x4_perspective(proj, 45, 1.7778f, 1, 100);
    qub3d::set_shader_mat4(shader, cam.view_mat(), "view");
    qub3d::set_shader_mat4(shader, proj, "proj");
 

    int use_camera = 0;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (use_camera)
        {
            int xvel = Keyboard::key(GLFW_KEY_W) - Keyboard::key(GLFW_KEY_S);
            int yvel = Keyboard::key(GLFW_KEY_SPACE) - Keyboard::key(GLFW_KEY_LEFT_SHIFT);
            int zvel = Keyboard::key(GLFW_KEY_D) - Keyboard::key(GLFW_KEY_A);
            cam.move(0.1f * xvel, 0.1f * yvel, 0.1f * zvel);

            if (Mouse::moving())
            {
                int yaw_offset, pitch_offset;
                Mouse::offset(yaw_offset, pitch_offset);
                cam.rotate(1.0f * yaw_offset, 1.0f * pitch_offset);
            }

            qub3d::set_shader_mat4(shader, cam.view_mat(), "view");

            if (Keyboard::key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                use_camera = 0;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
        else if (Keyboard::key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            use_camera = 1;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        Mouse::refresh();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
