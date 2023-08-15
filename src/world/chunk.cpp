#include "chunk.h"
#include <cassert>
#include <cstdlib>

namespace qub3d
{
    const int CHUNK_WIDTH  = 16;
    const int CHUNK_HEIGHT = 16;
    const int CHUNK_DEPTH  = 16;
    const int CHUNK_SIZE   = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH;

    // USEFUL FUNCTIONS

    static void get_xyz_indices(int i, int& xi_ref, int& yi_ref, int& zi_ref)
    {
        xi_ref = i % CHUNK_WIDTH;
        yi_ref = i / (CHUNK_WIDTH * CHUNK_DEPTH);
        zi_ref = (i / CHUNK_WIDTH) % CHUNK_DEPTH;
    }

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
        uint32_t indices_offset = 0;

        // for each block in chunk
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            // update lookup arrays
            vertex_lookup.push_back(vertices.size());
            index_lookup.push_back(indices.size());

            // get block model preset
            const BlockId block_id = chunk.blocks[i];
            Vertex* default_block_mesh = get_block_default_mesh(block_id);

            int xi, yi, zi;
            get_xyz_indices(i, xi, yi, zi);
            // translation vector for block[i] to put it in the right place in the world
            const vec3 offset = { xi, yi, zi };
            // translate block preset to be put in the right place
            for (int j = 0; j < 24; j++)
            {
                float* position = default_block_mesh[j].position;
                vec3_add(position, position, offset);
            }

            int j = 0; // how many vertices of block should be placed in the chunk

            if (no_block_right(chunk, xi, yi, zi))
            {
                for (int k = j; k < j + 4; k++)
                    vertices.push_back(default_block_mesh[k]);

                for (uint32_t index : face_indices_default)
                    indices.push_back(index + indices_offset);
                indices_offset += 4;
            }
            j += 4;

            if (no_block_top(chunk, xi, yi, zi))
            {
                for (int k = j; k < j + 4; k++)
                    vertices.push_back(default_block_mesh[k]);

                for (uint32_t index : face_indices_default)
                    indices.push_back(index + indices_offset);
                indices_offset += 4;
            }
            j += 4;

            if (no_block_front(chunk, xi, yi, zi))
            {
                for (int k = j; k < j + 4; k++)
                    vertices.push_back(default_block_mesh[k]);

                for (uint32_t index : face_indices_default)
                    indices.push_back(index + indices_offset);
                indices_offset += 4;
            }
            j += 4;

            if (no_block_left(chunk, xi, yi, zi))
            {
                for (int k = j; k < j + 4; k++)
                    vertices.push_back(default_block_mesh[k]);

                for (uint32_t index : face_indices_default)
                    indices.push_back(index + indices_offset);
                indices_offset += 4;
            }
            j += 4;

            if (no_block_bottom(chunk, xi, yi, zi))
            {
                for (int k = j; k < j + 4; k++)
                    vertices.push_back(default_block_mesh[k]);

                for (uint32_t index : face_indices_default)
                    indices.push_back(index + indices_offset);
                indices_offset += 4;
            }
            j += 4;

            if (no_block_back(chunk, xi, yi, zi))
            {
                for (int k = j; k < j + 4; k++)
                    vertices.push_back(default_block_mesh[k]);

                for (uint32_t index : face_indices_default)
                    indices.push_back(index + indices_offset);
                indices_offset += 4;
            }
            
            free(default_block_mesh);
        }
    }

}
