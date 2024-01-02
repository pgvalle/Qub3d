#pragma once

struct Keyboard {
  int keys[350], mods;

  bool is_key_pressed(int key) const {
    return keys[key] != 0;
  }

  bool are_mods_pressed(int mods_) const {
    return (mods_ & mods) == mods_;
  }
};