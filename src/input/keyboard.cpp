#include "keyboard.h"
#include <cstdarg>

namespace qub3d
{
	struct keyboard_data
	{
		int keys[350];
	};

	static keyboard_data keyboard = { { GLFW_RELEASE } };

	// IN HEADER

	int get_key(int key)
	{
		const int action = keyboard.keys[key];
		if (action == GLFW_PRESS)
		{
			keyboard.keys[key] = GLFW_REPEAT;
		}
		return action;
	}

	// CALLBACKS

	void key_callback(GLFWwindow* window, int key, int code, int action, int mods)
	{
		keyboard.keys[key] = action;
	}
}
