#pragma once

#include <linmath.h>

namespace qub3d
{
	class Camera
	{
	private:
		vec3 position;
		float yaw, pitch;
		float sensitivity;
		mat4x4 view;

	public:
		Camera()
			: position{ 0, 0, -1 }, yaw{ -90 }, pitch{ 0 }, sensitivity{ 0.5f }
		{
			rotate(0, 0);
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
