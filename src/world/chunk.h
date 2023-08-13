#ifndef QUB3D_CHUNK_H
#define QUB3D_CHUNK_H

#include <cstdint>
#include <linmath.h>

#define CHUNK_WIDTH  16  // x and z
#define CHUNK_HEIGHT 256 // y

#define CHUNK_SIZE (CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT)

struct qub3d_chunk
{
	int16_t blocks[CHUNK_SIZE];
	vec2 position; // position in world
};

qub3d_chunk* qub3d_generate_chunk();

// not fixed width arrays because amount of vertices will vary
struct qub3d_chunk_mesh
{
	vec3* vertices;
	size_t len_vertices;
	uint32_t* indices;
	size_t len_indices;
};

qub3d_chunk_mesh qub3d_build_chunk_mesh(const qub3d_chunk& chunk);

#endif // QUB3D_CHUNK_H