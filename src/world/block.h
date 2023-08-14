#pragma once

#include <cstdint>
#include <vector>
#include <linmath.h>

namespace qub3d
{
	enum BlockId
	{
		AIR = 0,
		WATER,
		SAND,
		GRASS,
		DIRT,
		STONE,
		COBBLESTONE
	};

	struct BlockVertex
	{
		vec3 position;
		vec2 uv;
	};

	struct BlockModel
	{
		std::vector<BlockVertex> vertices;
		std::vector<uint32_t> indices;

		// any faces in any possible model consist of 4 vertices
		// so size of vertices and indices is multiple of 4
		int face_count() const
		{
			return vertices.size() / 4;
		}
		
		static void generate_base_models();
		// Returns a copy of the original model.
		static BlockModel get_base_model(BlockId id);
		// modifies the model in-place
		void translate(float x_off, float y_off, float z_off, uint32_t index_off);
	};
}