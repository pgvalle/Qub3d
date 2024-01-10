#pragma once

#include "Vertex.h"
#include <initializer_list>

struct Quad {
  // I can iterate over the vertices
  // sizeof(Quad) = 4 * sizeof(Vertex)
  Vertex vertices[4];

  Quad();
  Quad(std::initializer_list<Vertex>&& vertices);

  void translate(float x, float y, float z);
};
