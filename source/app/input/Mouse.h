#pragma once

struct Mouse {
  int buttons[8], mods;

  int x, y;
  int lastx, lasty;

  void refresh();

  bool is_moving() const;
  
  void get_position(int* px, int* py) const;
  void get_offset(int* pxoff, int* pyoff) const;
};