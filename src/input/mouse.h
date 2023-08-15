#pragma once

#include <GLFW/glfw3.h>

namespace qub3d
{
    // call this every end of frame
    void refresh_mouse();

    void get_mouse_position(int& x_ref, int& y_ref);
    void get_mouse_offset(int& x_offset, int& y_offset);

    int get_mouse_button(int button);

    bool is_mouse_moving();
}
