#include "Quad.h"

#include <cstring>

static const float QUADS[6][20] = {
  // left
  -0.5f, -0.5f, -0.5f,   0, 0,
  -0.5f, -0.5f,  0.5f,   0, 0,
  -0.5f,  0.5f,  0.5f,   0, 0,
  -0.5f,  0.5f, -0.5f,   0, 0,
  // right
   0.5f, -0.5f,  0.5f,   0, 0,
   0.5f, -0.5f, -0.5f,   0, 0,
   0.5f,  0.5f, -0.5f,   0, 0,
   0.5f,  0.5f,  0.5f,   0, 0,
  // down
  -0.5f, -0.5f, -0.5f,   0, 0,
   0.5f, -0.5f, -0.5f,   0, 0,
   0.5f, -0.5f,  0.5f,   0, 0,
  -0.5f, -0.5f,  0.5f,   0, 0,
  // up
  -0.5f,  0.5f,  0.5f,   0, 0,
   0.5f,  0.5f,  0.5f,   0, 0,
   0.5f,  0.5f, -0.5f,   0, 0,
  -0.5f,  0.5f, -0.5f,   0, 0,
  // back
   0.5f, -0.5f, -0.5f,   0, 0,
  -0.5f, -0.5f, -0.5f,   0, 0,
  -0.5f,  0.5f, -0.5f,   0, 0,
   0.5f,  0.5f, -0.5f,   0, 0,
  // front
   0.5f, -0.5f,  0.5f,   0, 0,
   0.5f,  0.5f,  0.5f,   0, 0,
  -0.5f,  0.5f,  0.5f,   0, 0,
  -0.5f, -0.5f,  0.5f,   0, 0
};

Quad::Quad(Location location) {
  const int i = (int)location;
  memcpy(vertices, QUADS + i, sizeof(QUADS[i]));
}

void Quad::translate(float x, float y, float z) {
  const glm::vec3 offset = { x, y, z };
  for (Vertex& vertex : vertices) {
    vertex.position += offset;
  }
}
