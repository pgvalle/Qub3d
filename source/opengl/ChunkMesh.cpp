#include "ChunkMesh.h"
#include "Quad.h"

#include <cstdio>
#include <vector>
#include <cmath>

GLuint ChunkMesh::quadsEBOShared = 0;

void ChunkMesh::createQuadsSharedEBO() {
  if (quadsEBOShared) {
    printf("Quads Shared EBO already created!\n");
    return;
  }

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

  // creating opengl element buffer object
  glGenBuffers(1, &quadsEBOShared);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadsEBOShared);
  const GLsizeiptr elemsSize = sizeof(elems[0]) * elems.size();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elemsSize, elems.data(), GL_STATIC_DRAW);
}

void ChunkMesh::deleteQuadsSharedEBO() {
  if (quadsEBOShared) {
    glDeleteBuffers(1, &quadsEBOShared);
  }
}

ChunkMesh::ChunkMesh() {
  glGenVertexArrays(1, &quadsVAO);
  glGenBuffers(1, &quadsVBO);
}

void ChunkMesh::build(const Chunk& chunk) {
  std::vector<Quad> quads;
  for (int i = 0; i < Chunk::SIZE; i++) {
    int x, y, z;
    chunk.toPosition(i, x, y, z);

    if (!chunk.hasLeftNeighbor(i)) {
      quads.push_back({
        { { -0.5f, -0.5f, -0.5f }, { 0, 0 } },
        { { -0.5f, -0.5f,  0.5f }, { 1, 0 } },
        { { -0.5f,  0.5f,  0.5f }, { 1, 1 } },
        { { -0.5f,  0.5f, -0.5f }, { 0, 1 } }
      });
      quads.back().translate(x, y, z);
    }

    if (!chunk.hasRightNeighbor(i)) {
      quads.push_back({
        { { 0.5f, -0.5f,  0.5f }, { 0, 0 } },
        { { 0.5f, -0.5f, -0.5f }, { 1, 0 } },
        { { 0.5f,  0.5f, -0.5f }, { 1, 1 } },
        { { 0.5f,  0.5f,  0.5f }, { 0, 1 } }
      });
      quads.back().translate(x, y, z);
    }

    if (!chunk.hasDownNeighbor(i)) {
      quads.push_back({
        { { -0.5f, -0.5f, -0.5f }, { 0, 0 } },
        { {  0.5f, -0.5f, -0.5f }, { 1, 0 } },
        { {  0.5f, -0.5f,  0.5f }, { 1, 1 } },
        { { -0.5f, -0.5f,  0.5f }, { 0, 1 } }
      });
      quads.back().translate(x, y, z);
    }

    if (!chunk.hasUpNeighbor(i)) {
      quads.push_back({
        { { -0.5f,  0.5f,  0.5f }, { 0, 0 } },
        { {  0.5f,  0.5f,  0.5f }, { 1, 0 } },
        { {  0.5f,  0.5f, -0.5f }, { 1, 1 } },
        { { -0.5f,  0.5f, -0.5f }, { 0, 1 } }
      });
      quads.back().translate(x, y, z);
    }

    if (!chunk.hasBackNeighbor(i)) {
      quads.push_back({
        { {  0.5f, -0.5f, -0.5f }, { 0, 0 } },
        { { -0.5f, -0.5f, -0.5f }, { 1, 0 } },
        { { -0.5f,  0.5f, -0.5f }, { 1, 1 } },
        { {  0.5f,  0.5f, -0.5f }, { 0, 1 } }
      });
      quads.back().translate(x, y, z);
    }

    if (!chunk.hasFrontNeighbor(i)) {
      quads.push_back({
        { { -0.5f, -0.5f,  0.5f }, { 0, 0 } },
        { {  0.5f, -0.5f,  0.5f }, { 1, 0 } },
        { {  0.5f,  0.5f,  0.5f }, { 1, 1 } },
        { { -0.5f,  0.5f,  0.5f }, { 0, 1 } }
      });
      quads.back().translate(x, y, z);
    }
  }

  glBindVertexArray(quadsVAO);

  glBindBuffer(GL_ARRAY_BUFFER, quadsVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Quad) * quads.size(), quads.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vertex::position)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadsEBOShared);

  glBindVertexArray(0); // unbind to prevent trouble
}

void ChunkMesh::render() const {
  glBindVertexArray(quadsVAO);

  // draw quads (cubic blocks)
  GLint vertexBufferSize;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vertexBufferSize);
  const GLuint quadsElemsValid = 6 * (vertexBufferSize / sizeof(Quad));
  glDrawElements(GL_TRIANGLES, quadsElemsValid, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}
