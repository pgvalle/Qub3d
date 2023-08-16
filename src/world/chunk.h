#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <linmath.h>

#include "block.h"

namespace qub3d
{
    const int CHUNK_WIDTH  = 8;
    const int CHUNK_HEIGHT = 8;
    const int CHUNK_DEPTH  = 8;
    const int CHUNK_SIZE   = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH;

    struct Chunk
    {
        BlockId* blocks = nullptr;

        void generate();
    };

    struct ChunkMesh
    {
        std::vector<Vertex> vertices;
        // vertex_lookup[i] points to where the first vertex of block[i] is in vertex array
        // really important for world editing
        std::array<uint32_t, CHUNK_SIZE> vertex_lookup;

        std::vector<uint32_t> indices;
        // index_lookup[i] points to where the first index of block[i] is in index array
        // also important for world editing
        std::array<uint32_t, CHUNK_SIZE> index_lookup;

        const Vertex* vertex_data() const
        {
            return vertices.data();
        }

        size_t vertex_buffer_size() const
        {
            return sizeof(Vertex) * vertices.size();
        }

        const uint32_t* index_data() const
        {
            return indices.data();
        }

        size_t index_buffer_size() const
        {
            return sizeof(uint32_t) * indices.size();
        }

        void build(Chunk chunk);
        void remove(Chunk chunk);
    };
}
