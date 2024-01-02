#pragma once

#include <vector>
#include <array>

#include "./Block.h"
#include "opengl/Quad.h"

#define CHUNK_WIDTH  16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH  256
#define CHUNK_SIZE   (CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH)

struct Chunk {
  std::array<BlockID, CHUNK_SIZE> blocks;
  // block states
  // std::map<uint16_t, > states;

  Chunk();
};

struct ChunkMesh {
  std::vector<QuadVertices> vertices;
  std::vector<QuadIndices> indices;
  // tells where the mesh of a block starts and where it ends
  // important for world editing later
  std::array<uint16_t, CHUNK_SIZE + 1> block2quad;
};