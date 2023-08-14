#include "chunk.h"
#include <cstdlib>

#define MACRO()

namespace qub3d
{
	const int CHUNK_WIDTH  = 16;
	const int CHUNK_HEIGHT = 256;
	const int CHUNK_SIZE   = (CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT);

	static int get_1d_mapping(int xi, int yi, int zi)
	{
		const int mapping = CHUNK_WIDTH * CHUNK_WIDTH * yi + CHUNK_WIDTH * zi + xi;
		const bool in_bounds = 0 <= mapping && mapping < CHUNK_SIZE;
		return in_bounds ? mapping : -1;
	}

	void Chunk::generate()
	{
		blocks = (BlockId*)malloc(CHUNK_SIZE * sizeof(*blocks));
		for (int yi = 0; yi < CHUNK_HEIGHT; yi++)
		{
			for (int zi = 0; zi < CHUNK_WIDTH; zi++)
			{
				for (int xi = 0; xi < CHUNK_WIDTH; xi++)
				{
					int i = get_1d_mapping(xi, yi, zi);
					if (yi < 20)
					{
						blocks[i] = BlockId::DIRT;
					}
					else
					{
						blocks[i] = BlockId::AIR;
					}
				}
			}
		}
	}

	void ChunkMesh::build(Chunk chunk)
	{
		vertices = (BlockVertex*)malloc(24 * CHUNK_SIZE * sizeof(*vertices));	
		indices = (uint32_t*)malloc(36 * CHUNK_SIZE * sizeof(*indices));

		float x_off = 0.5f, y_off = 0.5f, z_off = -0.5f;
		int indices_off = 0;

		for (int yi = 0; yi < CHUNK_HEIGHT; yi++)
		{
			for (int zi = 0; zi < CHUNK_WIDTH; zi++)
			{
				for (int xi = 0; xi < CHUNK_WIDTH; xi++)
				{
					const int i = get_1d_mapping(xi, yi, zi);

					BlockModel model = BlockModel::get_base_model(chunk.blocks[i]);
					if (chunk.blocks[i] != BlockId::AIR)
					{
						model.translate(x_off, y_off, z_off, indices_off);
					}

					// copy it to chunk mesh
					memcpy(&vertices[len_vertices], model.vertices, model.len_vertices * sizeof(*vertices));
					len_vertices += model.len_vertices;

					memcpy(&indices[len_indices], model.indices, model.len_indices * sizeof(*indices));
					len_indices += model.len_indices;

					indices_off += model.len_vertices;
					x_off += 1;
				}

				x_off = 0.5f;
				z_off += 1;
			}

			z_off = -0.5f;
			y_off += 1;
		}
	}
}

