#include "Chunk.h"
#include <cstdio>

int Chunk::toIndex(int x, int y, int z) const {
  if (x < 0 || x >= Chunk::WIDTH) {
    return -1;
  }
  if (y < 0 || y >= Chunk::HEIGHT) {
    return -1;
  }
  if (z < 0 || z >= Chunk::DEPTH) {
    return -1;
  }
  return x + WIDTH * (DEPTH * y + z);
}

void Chunk::toPosition(int i, int& x, int& y, int& z) const {
  x = i % WIDTH;
  y = i / (WIDTH * DEPTH);
  z = (i % (WIDTH * DEPTH)) / WIDTH;
}

bool Chunk::hasLeftNeighbor(int i) const {
  int x, y, z;
  toPosition(i, x, y, z);
  int j = toIndex(x - 1, y, z);
  if (j == -1) {
    return false;
  }
  return blocks[j] != 0;
}

bool Chunk::hasRightNeighbor(int i) const {
  int x, y, z;
  toPosition(i, x, y, z);
  int j = toIndex(x + 1, y, z);
  if (j == -1) {
    return false;
  }
  return blocks[j] != 0;
}

bool Chunk::hasDownNeighbor(int i) const {
  int x, y, z;
  toPosition(i, x, y, z);
  int j = toIndex(x, y - 1, z);
  if (j == -1) {
    return false;
  }
  return blocks[j] != 0;
}

bool Chunk::hasUpNeighbor(int i) const {
  int x, y, z;
  toPosition(i, x, y, z);
  int j = toIndex(x, y + 1, z);
  if (j == -1) {
    return false;
  }
  return blocks[j] != 0;
}

bool Chunk::hasBackNeighbor(int i) const {
  int x, y, z;
  toPosition(i, x, y, z);
  int j = toIndex(x, y, z - 1);
  if (j == -1) {
    return false;
  }
  return blocks[j] != 0;
}

bool Chunk::hasFrontNeighbor(int i) const {
  int x, y, z;
  toPosition(i, x, y, z);
  int j = toIndex(x, y, z + 1);
  if (j == -1) {
    return false;
  }
  return blocks[j] != 0;
}
