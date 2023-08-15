#include "chunk.h"
#include <cassert>
#include <cstdlib>

namespace qub3d
{
    const int CHUNK_WIDTH  = 16;
    const int CHUNK_HEIGHT = 256;
    const int CHUNK_DEPTH  = 16;
    const int CHUNK_SIZE   = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH;

    // USEFUL FUNCTIONS

    static int get_array_index(int xi, int yi, int zi)
    {
        // in range in all axis.
        // This will help checking for surrounding air blocks
        const bool in_range = 0 <= xi && xi < CHUNK_WIDTH &&
            0 <= yi && yi < CHUNK_HEIGHT && 0 <= zi && zi < CHUNK_DEPTH;
        const int index = CHUNK_WIDTH * CHUNK_DEPTH * yi + CHUNK_WIDTH * zi + xi;
        return (in_range) ? index : -1;
    }

    static bool no_block_right(Chunk chunk, int xi, int yi, int zi)
    {
        const int index = get_array_index(xi + 1, yi, zi);
        return index < 0 || chunk.blocks[index] == 0;
    }

    static bool no_block_top(Chunk chunk, int xi, int yi, int zi)
    {
        const int index = get_array_index(xi, yi + 1, zi);
        return index < 0 || chunk.blocks[index] == 0;
    }

    static bool no_block_front(Chunk chunk, int xi, int yi, int zi)
    {
        const int index = get_array_index(xi, yi, zi + 1);
        return index < 0 || chunk.blocks[index] == 0;
    }

    static bool no_block_left(Chunk chunk, int xi, int yi, int zi)
    {
        const int index = get_array_index(xi - 1, yi, zi);
        return index < 0 || chunk.blocks[index] == 0;
    }

    static bool no_block_bottom(Chunk chunk, int xi, int yi, int zi)
    {
        const int index = get_array_index(xi, yi - 1, zi);
        return index < 0 || chunk.blocks[index] == 0;
    }

    static bool no_block_back(Chunk chunk, int xi, int yi, int zi)
    {
        const int index = get_array_index(xi, yi, zi - 1);
        return index < 0 || chunk.blocks[index] == 0;
    }

    // IN HEADER

    void Chunk::generate()
    {
        blocks = (BlockId*)malloc(CHUNK_SIZE * sizeof(*blocks));
        for (int yi = 0; yi < CHUNK_HEIGHT; yi++)
        {
            for (int zi = 0; zi < CHUNK_DEPTH; zi++)
            {
                for (int xi = 0; xi < CHUNK_WIDTH; xi++)
                {
                    const int i = get_array_index(xi, yi, zi);
                    blocks[i] = 1;
                }
            }
        }
    }

    void ChunkMesh::build(Chunk chunk)
    {
        const uint32_t face_indices_default[] = { 0, 1, 2, 2, 3, 0 };
        uint32_t indices_off = 0;

        for (int yi = 0; yi < CHUNK_HEIGHT; yi++)
        {
            for (int zi = 0; zi < CHUNK_DEPTH; zi++)
            {
                for (int xi = 0; xi < CHUNK_WIDTH; xi++)
                {
                    const int i = get_array_index(xi, yi, zi);
                    const BlockId block = chunk.blocks[i];
                    const Vertex* mesh = get_block_default_mesh(block);

                    for (int j = 0; j < 24; j++)
                    {
                        vertices.push_back(mesh[j]);
                        Vertex& vertex = vertices.back();
                        const vec3 offset = { xi, yi, zi };
                        vec3_add(vertex.position, vertex.position, offset);
                    }

                    // block[i] indices are located in position indices_off inside indices array.
                    index_lookup.push_back(indices_off);

                    // 1. air block surroudings check

                    if (no_block_right(chunk, xi, yi, zi))
                    {
                        for (uint32_t index : face_indices_default)
                        {
                            indices.push_back(index + indices_off);
                        }
                    }
                    indices_off += 4;

                    if (no_block_top(chunk, xi, yi, zi))
                    {
                        for (uint32_t index : face_indices_default)
                        {
                            indices.push_back(index + indices_off);
                        }
                    }
                    indices_off += 4;

                    if (no_block_front(chunk, xi, yi, zi))
                    {
                        for (uint32_t index : face_indices_default)
                        {
                            indices.push_back(index + indices_off);
                        }
                    }
                    indices_off += 4;

                    if (no_block_left(chunk, xi, yi, zi))
                    {
                        for (uint32_t index : face_indices_default)
                        {
                            indices.push_back(index + indices_off);
                        }
                    }
                    indices_off += 4;

                    if (no_block_bottom(chunk, xi, yi, zi))
                    {
                        for (uint32_t index : face_indices_default)
                        {
                            indices.push_back(index + indices_off);
                        }
                    }
                    indices_off += 4;

                    if (no_block_back(chunk, xi, yi, zi))
                    {
                        for (uint32_t index : face_indices_default)
                        {
                            indices.push_back(index + indices_off);
                        }
                    }
                    indices_off += 4;

                    // 2. know which faces not to include
                    // 3. add incices corresponding to faces that should be included
                }
            }
        }
    }
}
