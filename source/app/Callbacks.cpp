#include "Internal.h"
#include <glm/gtc/matrix_transform.hpp>


void framebuffer_size_callback(GLFWwindow* win, int w, int h) {
  // correct perspective matrix aspect ratio
  app.proj = glm::perspectiveFov(45.0f, 800.0f, 450.0f, 1.0f, 100.0f);
  // upload it to shader in use
  const GLint location = glGetUniformLocation(app.shader.ID, "proj");
  glUniformMatrix4fv(location, 1, GL_FALSE, &app.proj[0][0]);
  // so that the above work
  glViewport(0, 0, w, h);
}

void key_callback(GLFWwindow* win, int key, int scan, int action, int mods) {
  Keyboard& k = app.keyboard;
  k.keys[key] = action;
  k.mods = mods;
}

void char_callback(GLFWwindow* win, unsigned int codepoint) {
  // unused for now
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
  Mouse& m = app.mouse;
  m.buttons[button] = action;
  m.mods = mods;
}

void cursor_position_callback(GLFWwindow* win, double x, double y) {
  Mouse& m = app.mouse;
  m.lastx = m.x;
  m.lasty = m.y;
  m.x = (int)x;
  m.y = (int)y;
}

void cursor_enter_callback(GLFWwindow* win, int entered) {
  Mouse& m = app.mouse;
  // fix position bug
  double x, y;
  glfwGetCursorPos(win, &x, &y);
  m.lastx = m.x = (int)x;
  m.lasty = m.y = (int)y;
}
