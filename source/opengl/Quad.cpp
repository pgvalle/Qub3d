#include "Quad.h"
#include <stdexcept>

Quad::Quad() {}

Quad::Quad(std::initializer_list<Vertex>&& verts) {
  if (verts.size() > 4) {
    throw std::out_of_range("initializer list must have size <= 4!");
  }

  for (int i = 0; i < 4; i++) {
    vertices[i] = *(verts.begin() + i);
  }
}

void Quad::translate(float x, float y, float z) {
  const glm::vec3 offset = { x, y, z };
  for (Vertex& vertex : vertices) {
    vertex.position += offset;
  }
}
