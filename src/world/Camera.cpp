#include "camera.h"
#include <cmath>

static const vec3 UP = { 0, 1, 0 };

namespace qub3d
{
    void Camera::rotate(float yaw_off, float pitch_off)
    {
        yaw += sensitivity * yaw_off;
        pitch -= sensitivity * pitch_off;

        // Prevent players of breaking their necks LOL.
        // direction and up can't be parallel. It would mess up the view matrix.
        if (pitch >= 89.9f) pitch = 89.9f; // 90 or -90 means direction and up are parallel.
        else if (pitch <= -89.9f) pitch = -89.9f;

        // PI/180 = 0.01745329251
        const float yaw_rad = 0.01745329251f * yaw;
        const float pitch_rad = 0.01745329251f * pitch;

        const vec3 direction = {
            cosf(yaw_rad) * cosf(pitch_rad),
            sinf(pitch_rad),
            sinf(yaw_rad) * cosf(pitch_rad)
        };
        vec3 center;
        vec3_add(center, position, direction);

        mat4x4_look_at(view, position, center, UP);
    }

    void Camera::move(float xvel, float yvel, float zvel)
    {
        mat4x4_translate_in_place(view, position[0], position[1], position[2]);

        vec3 front = { -view[0][2], 0, -view[2][2] };
        vec3_scale(front, front, xvel / vec3_len(front));
        vec3_add(position, position, front);

        vec3 up;
        vec3_scale(up, UP, yvel);
        vec3_add(position, position, up);

        vec3 right = { view[0][0], view[1][0], view[2][0] };
        vec3_scale(right, right, zvel);
        vec3_add(position, position, right);

        mat4x4_translate_in_place(view, -position[0], -position[1], -position[2]);
    }
}
