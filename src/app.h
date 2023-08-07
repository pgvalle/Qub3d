#ifndef QUB3D_APP_H
#define QUB3D_APP_H

#include <GLFW/glfw3.h>


struct mouse_data_t {
	int x, y;
	int last_x, last_y;
	int moving;

	int buttons[8];
	int mods;
};

struct keyboard_data_t {
	int keys[350];
	int mods;
};

struct app_data_t {
	GLFWwindow* window;

	struct mouse_data_t mouse;
	struct keyboard_data_t keyboard;
};

// singleton
extern struct app_data_t app;


#endif // QUB3D_APP_H