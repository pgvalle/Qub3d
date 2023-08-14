#pragma once

#include <cstdint>
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
		BlockVertex* vertices = nullptr;
		size_t len_vertices = 0;

		uint32_t* indices = nullptr;
		size_t len_indices = 0;

		static void generate_base_models();
		// Returns a copy of the original model.
		static BlockModel get_base_model(BlockId id);
		// modifies the model in-place
		void translate(float x_off, float y_off, float z_off, uint32_t index_off);
	};
}