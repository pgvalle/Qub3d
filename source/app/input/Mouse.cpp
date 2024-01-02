#include "Mouse.h"


void Mouse::refresh() {
  lastx = x;
  lasty = y;
}

bool Mouse::is_moving() const {
  return lastx != x || lasty != y;
}

void Mouse::get_position(int* px, int* py) const {
  if (px) *px = x;
  if (py) *py = y;
}

void Mouse::get_offset(int* pxoff, int* pyoff) const {
  if (pxoff) *pxoff = x - lastx;
  if (pyoff) *pyoff = y - lasty;
}