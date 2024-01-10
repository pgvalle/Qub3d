#pragma once

#include <glad.h>

class Chunk {
public:
  static const int WIDTH  = 16,  // x
                   HEIGHT = 256, // y
                   DEPTH  = 16,  // z
                   SIZE   = WIDTH * HEIGHT * DEPTH;

public:
  short blocks[SIZE];

  int toIndex(int x, int y, int z) const;
  void toPosition(int i, int& x, int& y, int& z) const;

public:
  Chunk() {
    for (int i = 0; i < SIZE; i++) {
      blocks[i] = 1;
    }
  }

  bool hasLeftNeighbor(int i) const;
  bool hasRightNeighbor(int i) const;
  bool hasDownNeighbor(int i) const;
  bool hasUpNeighbor(int i) const;
  bool hasBackNeighbor(int i) const;
  bool hasFrontNeighbor(int i) const;
};
