#ifndef QUB3D_CAMERA_H
#define QUB3D_CAMERA_H

#include <linmath.h>

typedef struct qub3d_camera_t
{
	vec3 position;
	float yaw, pitch;
	float sensitivity;
	mat4x4 view;
} qub3d_camera_t;

void qub3d_init_camera(qub3d_camera_t* cam);
void qub3d_rotate_camera(qub3d_camera_t* cam, float yaw_off, float pitch_off);
// x, y and z in camera space.
// x: forward(+) or back(-)
// y: up(+) or down(-)
// z: right(+) or left(-)
void qub3d_move_camera(qub3d_camera_t* cam, float xvel, float yvel, float zvel);

#endif // QUB3D_CAMERA_H