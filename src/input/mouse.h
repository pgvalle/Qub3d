#ifndef QUB3D_MOUSE_H
#define QUB3D_MOUSE_H

#include <GLFW/glfw3.h>

void qub3d_refresh_mouse();

void qub3d_get_mouse_position(int* x, int* y);
void qub3d_get_mouse_offset(int* x_offset, int* y_offset);

int qub3d_mouse_button(int button);

int qub3d_mouse_mods_equal(int mods);

int qub3d_mouse_moving();

#endif // QUB3D_MOUSE_H