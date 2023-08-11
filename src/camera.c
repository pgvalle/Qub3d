#include "camera.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

static const vec3 UP = { 0, 1, 0 };

void qub3d_init_camera(qub3d_camera_t* cam)
{
	assert(cam);

	*cam = (qub3d_camera_t) {
		.position = { 0, 0, -1 },
		.yaw = -90, .pitch = 0,
		.sensitivity = 0.5
	};

	qub3d_rotate_camera(cam, 0, 0);
}

void qub3d_rotate_camera(qub3d_camera_t* cam, float yaw_off, float pitch_off)
{
	assert(cam);

	cam->yaw += cam->sensitivity * yaw_off;
	cam->pitch -= cam->sensitivity * pitch_off;

	// Prevent players of breaking their necks LOL.
	// direction and up can't be parallel. It would mess up the view matrix.
	if (cam->pitch >= 89.9f)
	{
		cam->pitch = 89.9f; // 90 or -90 means direction and up are parallel.
	}
	else if (cam->pitch <= -89.9f)
	{
		cam->pitch = -89.9f;
	}
	
	// PI/180 = 0.01745329251
	const float yaw_rad = 0.01745329251f * cam->yaw;
	const float pitch_rad = 0.01745329251f * cam->pitch;

	const vec3 direction = {
		cosf(yaw_rad) * cosf(pitch_rad),
		sinf(pitch_rad),
		sinf(yaw_rad) * cosf(pitch_rad)
	};
	vec3 center;
	vec3_add(center, cam->position, direction);

	mat4x4_look_at(cam->view, cam->position, center, UP);
}

void qub3d_move_camera(qub3d_camera_t* cam, float xvel, float yvel, float zvel)
{
	mat4x4_translate_in_place(cam->view, cam->position[0], cam->position[1], cam->position[2]);

	vec3 front = { -cam->view[0][2], 0, -cam->view[2][2] };
	vec3_scale(front, front, xvel / vec3_len(front));
	vec3_add(cam->position, cam->position, front);

	vec3 up;
	vec3_scale(up, UP, yvel);
	vec3_add(cam->position, cam->position, up);

	vec3 right = { cam->view[0][0], cam->view[1][0], cam->view[2][0] };
	vec3_scale(right, right, zvel);
	vec3_add(cam->position, cam->position, right);

	mat4x4_translate_in_place(cam->view, -cam->position[0], -cam->position[1], -cam->position[2]);
}