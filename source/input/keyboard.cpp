#include "keyboard.h"
#include <cstdarg>

namespace Keyboard {
  int keys[350] = { GLFW_RELEASE };

  int key(int k) {
    const int action = keys[k];
    if (action == GLFW_PRESS) {
      keys[k] = GLFW_REPEAT;
    }
    return action;
  }

  void key_callback(GLFWwindow* window, int key, int code, int action, int mods) {
    keys[key] = action;
  }
}
