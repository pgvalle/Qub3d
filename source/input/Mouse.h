#pragma once

#include <GLFW/glfw3.h>

class Mouse {
private:
  int buttons[8], mods;
  int x, y;
  int lastX, lastY;

public:
  Mouse() {}
  Mouse(GLFWwindow* window);

  bool isMoving() const;

  int getButton(int button);
  void getPosition(int* px, int* py) const;
  void getOffset(int* pxoff, int* pyoff) const;

  void refresh();
};