#include <GLFW/glfw3.h>

namespace Mouse {
  int xpos = -1, ypos = -1;
  int lastx = -1, lasty = -1;

  bool inside = false;

  int buttons[8] = { GLFW_RELEASE };


  void refresh() {
    // assume delta is zero every frame.
    // Otherwise delta will always be non-null even if the mouse isn't moving.
    lastx = xpos;
    lasty = ypos;
  }

  void position(int& x, int& y) {
    x = xpos;
    y = ypos;
  }

  void offset(int& xoff, int& yoff) {
    xoff = xpos - lastx;
    yoff = ypos - lasty;
  }

  int button(int b) {
    return buttons[b];
  }

  bool moving() {
    return xpos != lastx || ypos != lasty;
  }


  void pos_callback(GLFWwindow* win, double newx, double newy) {
    lastx = xpos;
    lasty = ypos;
    xpos = (int)newx;
    ypos = (int)newy;
  }

  void button_callback(GLFWwindow* window, int button, int action, int mods) {
    buttons[button] = action;
  }

  void enter_callback(GLFWwindow* window, int entered) {
    // fix cursor delta when entering window again
    double newx, newy;
    glfwGetCursorPos(window, &newx, &newy);
    lastx = xpos = newx;
    lasty = ypos = newy;

    inside = (bool)entered;
  }
}
