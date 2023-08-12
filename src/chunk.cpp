#include "chunk.h"
#include <cstdlib>

qub3d_chunk* qub3d_generate_chunk()
{
	qub3d_chunk* chunk = (qub3d_chunk*)malloc(sizeof(*chunk));
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		const uint32_t value = rand() % 3;
		chunk->blocks[i] = value == 0;
	}

	return chunk;
}

qub3d_chunk_mesh qub3d_build_chunk_mesh(const qub3d_chunk& chunk)
{
	float x_off = 1.5, y_off = 0.5, z_off = -10.5;

	vec3* vertices = (vec3*)malloc(24 * CHUNK_SIZE * sizeof(*vertices));
	uint32_t* indices = (uint32_t*)malloc(36 * CHUNK_SIZE * sizeof(*indices));
	size_t len_vertices = 0, len_indices = 0;

	int index_offset = 0;
	
	// for each chunk block, create the block
	for (int yi = 0; yi < CHUNK_HEIGHT; yi++)
	{
		for (int zi = 0; zi < CHUNK_WIDTH; zi++)
		{
			for (int xi = 0; xi < CHUNK_WIDTH; xi++)
			{
				const int i = CHUNK_WIDTH * CHUNK_WIDTH * yi + CHUNK_WIDTH * zi + xi;
					// for each block face, push vertices of that face and indices to their arrays
					// bottom
					vec3 vertices_bot[] = {
						{ x_off + 0.5f, y_off - 0.5f, z_off + 0.5f },
						{ x_off - 0.5f, y_off - 0.5f, z_off + 0.5f },
						{ x_off - 0.5f, y_off - 0.5f, z_off - 0.5f },
						{ x_off + 0.5f, y_off - 0.5f, z_off - 0.5f }
					};
					memcpy(&vertices[len_vertices], vertices_bot, sizeof(vertices_bot));
					len_vertices += 4;

					uint32_t indices_bot[] = { 0, 1, 2, 0, 2, 3 };
					for (int j = 0; j < 6; j++)
					{
						indices[len_indices++] = index_offset + indices_bot[j];
					}
					index_offset += 4;


				x_off += 1;
			}

			x_off = 1.5f;
			z_off += 1;
		}

		z_off = -10.5f;
		y_off += 1;
	}

	return { vertices, len_vertices, indices, len_indices };
}
