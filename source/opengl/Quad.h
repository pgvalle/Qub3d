#pragma once

#include "Vertex.h"

struct Quad {
  enum class Location {
    LEFT = 0, RIGHT,
    DOWN, UP,
    BACK, FRONT
  };

  Vertex vertices[4];

  Quad(Location location);

  // useful for ChunkMesh construction
  void translate(float x, float y, float z);
};
