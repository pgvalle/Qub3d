#pragma once

#include <cstdint>
#include <linmath.h>

#include "block.h"

namespace qub3d
{
	struct Chunk
	{
		BlockId* blocks = nullptr;

		void generate();
	};

	struct ChunkMesh : BlockModel
	{
		void build(Chunk chunk);
	};
}
