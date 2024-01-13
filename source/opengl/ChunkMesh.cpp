#include "ChunkMesh.h"
#include "Quad.h"

#include <cstdio>
#include <vector>
#include <cmath>

static GLuint quadsEBOShared = 0;

void ChunkMesh::createQuadsSharedEBO() {
  GLuint elemPattern[] = { 0, 1, 2, 0, 2, 3 };
  std::vector<GLuint> elems;

  // ceil(chunkSize / 2) maximizes the number of elements
  const int halfChunkSize = ceilf(Chunk::SIZE / 2.0f);

  for (int i = 0; i < halfChunkSize; i++) {
    for (int j = 0; j < 6; j++) {
      for (int k = 0; k < 6; k++) {
        elems.push_back(elemPattern[k]);
        elemPattern[k] += 4;
      }
    }
  }

  glGenBuffers(1, &quadsEBOShared);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadsEBOShared);
  const GLsizeiptr elemsSize = sizeof(GLuint) * elems.size();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elemsSize, elems.data(), GL_STATIC_DRAW);
}

void ChunkMesh::deleteQuadsSharedEBO() {
  glDeleteBuffers(1, &quadsEBOShared);
}

ChunkMesh::ChunkMesh() {
  quadsVAO = 0;
}

void ChunkMesh::build(const Chunk& chunk) {

  std::vector<Quad> quads;
  for (int i = 0; i < Chunk::SIZE; i++) {
    int x, y, z;
    chunk.toPosition(i, x, y, z);

    if (!chunk.hasLeftNeighbor(i)) {
      Quad quad(Quad::Location::LEFT);
      quad.translate(x, y, z);
      quads.push_back(quad);
    }

    if (!chunk.hasRightNeighbor(i)) {
      Quad quad(Quad::Location::RIGHT);
      quad.translate(x, y, z);
      quads.push_back(quad);
    }

    if (!chunk.hasDownNeighbor(i)) {
      Quad quad(Quad::Location::DOWN);
      quad.translate(x, y, z);
      quads.push_back(quad);
    }

    if (!chunk.hasUpNeighbor(i)) {
      Quad quad(Quad::Location::UP);
      quad.translate(x, y, z);
      quads.push_back(quad);
    }

    if (!chunk.hasBackNeighbor(i)) {
      Quad quad(Quad::Location::BACK);
      quad.translate(x, y, z);
      quads.push_back(quad);
    }

    if (!chunk.hasFrontNeighbor(i)) {
      Quad quad(Quad::Location::FRONT);
      quad.translate(x, y, z);
      quads.push_back(quad);
    }
  }

  glGenVertexArrays(1, &quadsVAO);
  glBindVertexArray(quadsVAO);

  GLuint quadsVBO;
  glGenBuffers(1, &quadsVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadsVBO);
  const GLsizeiptr quadsSize = sizeof(Quad) * quads.size();
  glBufferData(GL_ARRAY_BUFFER, quadsSize, quads.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vertex::position)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadsEBOShared);

  glBindVertexArray(0); // to prevent trouble
}

void ChunkMesh::render() const {
  glBindVertexArray(quadsVAO);

  // draw quads (cubic blocks)
  GLint quadBufferSize;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &quadBufferSize);
  const GLuint quadsElemsValid = 6 * (quadBufferSize / sizeof(Quad));
  glDrawElements(GL_TRIANGLES, quadsElemsValid, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);

  // ...
}
