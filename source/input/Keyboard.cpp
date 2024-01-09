#include "App.h"
#include "Keyboard.h"

#include <cstring>

Keyboard::Keyboard(GLFWwindow* window) {
  // initializing fields
  memset(keys, 0, sizeof(keys));
  mods = 0;

  glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scan, int action, int mods) {
    Keyboard& k = ((App*)glfwGetWindowUserPointer(win))->keyboard;
    
    k.keys[key] = action;
    k.mods = mods;
  });
}

int Keyboard::getKey(int key) {
  return keys[key];
}
