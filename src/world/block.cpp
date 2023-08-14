#include "block.h"
#include <map>
#include <cstdlib>

namespace qub3d
{
	static std::map<BlockId, BlockModel> base_models;

	// each model generation function (REEEEEEEEALLY long section)
	void generate_dirt_model()
	{
		BlockModel model;

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

		uint32_t indices_offset = 0;

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
				
				model.vertices.push_back(vertex);
			}

			// append indices to mesh correctly so that opengl can render the face
			for (uint32_t i : { 0, 1, 2, 2, 3, 0 })
			{
				model.indices.push_back(i + indices_offset);
			}
			indices_offset += 4;
		}

		// don't waste memory
		model.vertices.shrink_to_fit();
		model.indices.shrink_to_fit();

		base_models[BlockId::DIRT] = model;
	}

	void BlockModel::generate_base_models()
	{
		generate_dirt_model();
		base_models[BlockId::AIR] = BlockModel(); // nothing
	}

	BlockModel BlockModel::get_base_model(BlockId id)
	{
		return base_models.at(id);
	}

	void BlockModel::translate(float x_off, float y_off, float z_off, uint32_t index_off)
	{
		// translating vertices
		const vec3 offset = { x_off, y_off, z_off };
		for (BlockVertex& vertex : vertices)
		{
			vec3_add(vertex.position, vertex.position, offset);
		}

		// translating indices
		for (uint32_t& index : indices)
		{
			index += index_off;
		}
	}
}