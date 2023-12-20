#pragma once

#include <GLFW/glfw3.h>

namespace Mouse {
  // call this every end of frame
  void refresh();

  void position(int& x, int& y);
  void offset(int& xoff, int& yoff);

  int button(int b);

  bool moving();


  void pos_callback(GLFWwindow* win, double newx, double newy);
  void button_callback(GLFWwindow* window, int button, int action, int mods);
  void enter_callback(GLFWwindow* window, int entered);
}
