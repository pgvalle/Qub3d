#include <GLFW/glfw3.h>

struct qub3d_mouse
{
	int x, y;
	int last_x, last_y;

	int inside;

	int buttons[8];
	int modifiers;
};

static qub3d_mouse mouse = { -1, -1, -1, -1, 0, { GLFW_RELEASE }, 0 };

// IN HEADER

void qub3d_refresh_mouse()
{
	// assume delta is zero every frame.
	// Otherwise delta will always be non-null even if the mouse isn't moving.
	mouse.last_x = mouse.x;
	mouse.last_y = mouse.y;
}

void qub3d_get_mouse_position(int* x, int* y)
{
	if (x) *x = mouse.x;
	if (y) *y = mouse.y;
}

void qub3d_get_mouse_offset(int* x_offset, int* y_offset)
{
	if (x_offset) *x_offset = mouse.x - mouse.last_x;
	if (y_offset) *y_offset = mouse.y - mouse.last_y;
}

int qub3d_mouse_button(int button)
{
	return mouse.buttons[button];
}

int qub3d_mouse_mods_equal(int mods)
{
	return mouse.modifiers == mods;
}

int qub3d_mouse_moving()
{
	return mouse.x != mouse.last_x || mouse.y != mouse.last_y;
}

// CALLBACKS

void qub3d_mouse_position_callback(GLFWwindow* win, double x, double y)
{
	mouse.last_x = mouse.x;
	mouse.last_y = mouse.y;
	mouse.x = (int)x;
	mouse.y = (int)y;
}

void qub3d_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	mouse.buttons[button] = action;
	mouse.modifiers = mods;
}

void qub3d_mouse_enter_callback(GLFWwindow* window, int entered)
{
	// fix cursor delta when entering window again
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	mouse.last_x = mouse.x = x;
	mouse.last_y = mouse.y = y;

	mouse.inside = entered;
}