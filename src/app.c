#include <glad.h>
#include "app.h"

struct app_data_t app = {
	.window = NULL,

	.mouse = {
		.x = -1, .y = -1,
		.last_x = -1, .last_y = -1,
		.moving = GLFW_FALSE,
		.buttons = { 0 },
		.mods = 0
	},

	.keyboard = {
		.keys = { 0 },
		.mods = 0
	}
};

#define MOUSE app.mouse

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	MOUSE.buttons[button] = action;
	MOUSE.mods = mods;
}

void mouse_motion_callback(GLFWwindow* window, double x, double y) {
	MOUSE.last_x = MOUSE.x;
	MOUSE.last_y = MOUSE.y;
	MOUSE.x = (int)x;
	MOUSE.y = (int)y;
}

void mouse_enter_callback(GLFWwindow* window, int entered) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	MOUSE.last_x = MOUSE.x = (int)x;
	MOUSE.last_y = MOUSE.y = (int)y;

	MOUSE.moving = GLFW_FALSE;
}

#define KEYBOARD app.keyboard

void key_callback(GLFWwindow* window, int key, int code, int action, int mods) {

}

void resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}