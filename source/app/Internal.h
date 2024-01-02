#pragma once

#include <cassert>
#include <cstdio>
#include <string>
#include <map>

#include <glad.h>
#include <GLFW/glfw3.h>

#include "./input/Input.h"
#include "opengl/Camera.h"
#include "opengl/Shader.h"

extern struct AppData {
  // low level

  GLFWwindow* win;
  Mouse mouse;
  Keyboard keyboard;

  // graphics

  mat4x4 proj;
  Camera cam;
  Shader shader;

  // resources

  GLuint blocks_atlas_id;
  //std::map<std::string, vec2[4]> blocks_atlas_uvs;
} app;

void load_and_pack_textures();

void framebuffer_size_callback(GLFWwindow* win, int w, int h);

void key_callback(GLFWwindow* win, int key, int scan, int action, int mods);
void char_callback(GLFWwindow* win, unsigned int codepoint);

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* win, double x, double y);
void cursor_enter_callback(GLFWwindow* win, int entered);