#pragma once

#include <GLFW/glfw3.h>

namespace Keyboard {
  int key(int k);

  void key_callback(GLFWwindow* window, int key, int code, int action, int mods);
}
