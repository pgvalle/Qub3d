#include "App.h"
#include "Keyboard.h"

Keyboard::Keyboard() {
  memset(keys, 0, sizeof(keys));
  mods = 0;
}

void Keyboard::installCallbacks(GLFWwindow* window) {
  glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scan, int action, int mods) {
    Keyboard& k = ((App*)glfwGetWindowUserPointer(win))->keyboard;
    
    k.keys[key] = action;
    k.mods = mods;
  });
}

int Keyboard::getKey(int key) {
  return keys[key];
}
