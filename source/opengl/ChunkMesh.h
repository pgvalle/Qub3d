#pragma once

#include <glad.h>
#include "world/Chunk.h"

class ChunkMesh {
private:
  // The EBO is shared bc quads have the same element pattern:
  // { n, n+1, n+2, n, n+2, n+3 }
  static GLuint quadsEBOShared;

  GLuint quadsVAO, quadsVBO;

public:
  static void createQuadsSharedEBO();
  static void deleteQuadsSharedEBO();

  ChunkMesh();

  void build(const Chunk& chunk);

  void render() const;
};
