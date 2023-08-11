#include "keyboard.h"

struct qub3d_keyboard_t
{
	int keys[350];
	int modifiers;
};

static struct qub3d_keyboard_t keyboard = { { GLFW_RELEASE }, 0 };

// IN HEADER

int qub3d_key(int key)
{
	return keyboard.keys[key];
}

// CALLBACKS

void qub3d_key_callback(GLFWwindow* window, int key, int code, int action, int mods)
{
	keyboard.keys[key] = action;
	keyboard.modifiers = mods;
}