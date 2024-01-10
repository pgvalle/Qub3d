#include "App.h"
#include "Mouse.h"

#include <cstring>


Mouse::Mouse() {
  memset(buttons, 0, sizeof(buttons));
  mods = 0;
  x = 0;
  y = 0;
  lastX = 0;
  lastY = 0;
}

void Mouse::installCallbacks(GLFWwindow* window) {
  glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
    Mouse& m = ((App*)glfwGetWindowUserPointer(win))->mouse;

    m.buttons[button] = action;
    m.mods = mods;
  });

  glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
    Mouse& m = ((App*)glfwGetWindowUserPointer(win))->mouse;

    m.lastX = m.x;
    m.lastY = m.y;
    m.x = (int)x;
    m.y = (int)y;
  });

  // fix lastX and lastY bug when cursor leaving then entering the window
  glfwSetCursorEnterCallback(window, [](GLFWwindow* win, int entered) {
    Mouse& m = ((App*)glfwGetWindowUserPointer(win))->mouse;

    // get current cursor position
    double x, y;
    glfwGetCursorPos(win, &x, &y);
    // set x, lastx, y and lasty to be that value
    m.lastX = m.x = (int)x;
    m.lastY = m.y = (int)y;
  });
}

bool Mouse::isMoving() const {
  return lastX != x || lastY != y;
}

int Mouse::getButton(int button) {
  return buttons[button];
}

void Mouse::getPosition(int* px, int* py) const {
  if (px) *px = x;
  if (py) *py = y;
}

void Mouse::getOffset(int* pxoff, int* pyoff) const {
  if (pxoff) *pxoff = x - lastX;
  if (pyoff) *pyoff = y - lastY;
}

void Mouse::refresh() {
  lastX = x;
  lastY = y;
}
