#include "keyboard.h"
#include <cstdarg>

namespace qub3d
{
	static int keys[350] = { GLFW_RELEASE };

	// IN HEADER

	int get_key(int key)
	{
		const int action = keys[key];
		if (action == GLFW_PRESS)
		{
			keys[key] = GLFW_REPEAT;
		}
		return action;
	}

	// CALLBACKS

	void key_callback(GLFWwindow* window, int key, int code, int action, int mods)
	{
		keys[key] = action;
	}
}
