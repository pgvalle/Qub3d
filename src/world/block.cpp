#include "block.h"
#include <map>
#include <cstdlib>
#include <cassert>
namespace qub3d
{
	static std::map<BlockId, BlockModel> base_models = std::map<BlockId, BlockModel>();

	// each model generation function (REEEEEEEEALLY long section)
	void generate_dirt_model()
	{
		BlockModel model;
		model.vertices = (BlockVertex*)malloc(24 * sizeof(*model.vertices));
		model.indices = (uint32_t*)malloc(36 * sizeof(*model.indices));

		const vec3 positions[8] = {
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f
		};

		const vec2 uvs[4] = { 0, 0,   0, 1,   1, 1,   1, 0 };

		// in correct order so that culling just works
		const uint32_t faces_indices[6][4] = {
			0, 1, 2, 3, // bottom face
			4, 5, 6, 7, // top
			1, 7, 6, 2, // left
			0, 3, 5, 4, // right
			2, 6, 5, 3, // back
			0, 4, 7, 1  // front
		};

		int indices_offset = 0;

		// for each face
		for (int f = 0; f < 6; f++)
		{
			// for each index that composes the face
			for (int i = 0; i < 4; i++)
			{
				// get corresponding vertex position
				const uint32_t face_index = faces_indices[f][i];
				// build vertex
				BlockVertex vertex;
				memcpy(vertex.position, positions[face_index], sizeof(vec3));
				memcpy(vertex.uv, uvs[i], sizeof(vec2));
				memcpy(&model.vertices[model.len_vertices++], &vertex, sizeof(vertex));
			}

			// append indices to mesh correctly so that opengl can render the face
			for (int i : { 0, 1, 2, 2, 3, 0 })
			{
				model.indices[model.len_indices++] = i + indices_offset;
			}
			indices_offset += 4;
		}

		base_models[BlockId::DIRT] = model;
	}

	void BlockModel::generate_base_models()
	{
		generate_dirt_model();
		base_models[BlockId::AIR] = BlockModel(); // nothing
	}

	BlockModel BlockModel::get_base_model(BlockId id)
	{
		const BlockModel base = base_models[id];
		BlockModel copy;

		copy.vertices = (BlockVertex*)malloc(base.len_vertices * sizeof(*copy.vertices));
		copy.indices = (uint32_t*)malloc(base.len_indices * sizeof(*copy.indices));

		// deep copy everything
		memcpy(copy.vertices, base.vertices, base.len_vertices * sizeof(*copy.vertices));
		copy.len_vertices = base.len_vertices;
		memcpy(copy.indices, base.indices, base.len_indices * sizeof(*copy.indices));
		copy.len_indices = base.len_indices;

		return copy;
	}

	void BlockModel::translate(float x_off, float y_off, float z_off, uint32_t index_off)
	{
		// translating vertices
		const vec3 offset = { x_off, y_off, z_off };
		for (int i = 0; i < len_vertices; i++)
		{
			vec3_add(vertices[i].position, vertices[i].position, offset);
		}

		// translating indices
		for (int i = 0; i < len_indices; i++)
		{
			indices[i] += index_off;
		}
	}
}