#include <GLFW/glfw3.h>

namespace qub3d
{
    static int x = -1, y = -1;
    static int last_x = -1, last_y = -1;

    static bool inside = false;

    static int buttons[8] = { GLFW_RELEASE };


    // IN HEADER

    void refresh_mouse()
    {
        // assume delta is zero every frame.
        // Otherwise delta will always be non-null even if the mouse isn't moving.
        last_x = x;
        last_y = y;
    }

    void get_mouse_position(int& x_ref, int& y_ref)
    {
        x_ref = x;
        y_ref = y;
    }

    void get_mouse_offset(int& x_offset, int& y_offset)
    {
        x_offset = x - last_x;
        y_offset = y - last_y;
    }

    int get_mouse_button(int button)
    {
        return buttons[button];
    }

    bool is_mouse_moving()
    {
        return x != last_x || y != last_y;
    }

    // CALLBACKS

    void mouse_position_callback(GLFWwindow* win, double new_x, double new_y)
    {
        last_x = x;
        last_y = y;
        x = (int)new_x;
        y = (int)new_y;
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        buttons[button] = action;
    }

    void mouse_enter_callback(GLFWwindow* window, int entered)
    {
        // fix cursor delta when entering window again
        double new_x, new_y;
        glfwGetCursorPos(window, &new_x, &new_y);
        last_x = x = new_x;
        last_y = y = new_y;

        inside = (bool)entered;
    }
}
