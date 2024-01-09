#pragma once

#include <GLFW/glfw3.h>

class Keyboard {
private:
  int keys[350], mods;

public:
  Keyboard() {}
  Keyboard(GLFWwindow* window);

  int getKey(int key);
};