#pragma once

#include <glad.h>

#include "world/Chunk.h"

class ChunkMesh {
private:
  GLuint quadsVAO;

public:
  // this won't work in another opengl context
  static void createQuadsSharedEBO();
  static void deleteQuadsSharedEBO();

  ChunkMesh();

  void build(const Chunk& chunk);

  void render() const;
};
