#pragma once

#include <linmath.h>

namespace qub3d
{
    class Camera
    {
    private:
        vec3 position = { 0, 0, 0 };
        float yaw = 0, pitch = 0;
        float sensitivity = 0.5f;
        mat4x4 view;

    public:
        Camera::Camera()
        {
            rotate(0, 0); // look in the direction of (1, 0, 0)
        }

        const vec4* get_view_mat() const
        {
            return &view[0];
        }

        void rotate(float yay_off, float pitch_off);
        // x, y and z in camera space.
        // x: forward(+) or back(-)
        // y: up(+) or down(-)
        // z: right(+) or left(-)
        void move(float xvel, float yvel, float zvel);
    };
}
