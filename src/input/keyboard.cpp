#include "keyboard.h"

struct qub3d_keyboard
{
	int keys[350];
	int modifiers;
};

static qub3d_keyboard keyboard = { { GLFW_RELEASE }, 0 };

// IN HEADER

int qub3d_key(int key)
{
	const int action = keyboard.keys[key];
	if (action == GLFW_PRESS)
	{
		keyboard.keys[key] = GLFW_REPEAT;
	}
	return action;
}

// CALLBACKS

void qub3d_key_callback(GLFWwindow* window, int key, int code, int action, int mods)
{
	keyboard.keys[key] = action;
	keyboard.modifiers = mods;
}