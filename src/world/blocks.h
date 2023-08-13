#pragma once

#include <cstdint>
#include <linmath.h>

struct qub3d_vertex
{
	vec3 position;
	vec2 uvs;
};

void qub3d_load_blocks();