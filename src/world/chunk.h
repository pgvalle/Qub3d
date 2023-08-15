#pragma once

#include <cstdint>
#include <vector>
#include <linmath.h>

#include "block.h"

namespace qub3d
{
    struct Chunk
    {
        BlockId* blocks = nullptr;

        void generate();
    };

    struct ChunkMesh
    {
        std::vector<Vertex> vertices;
        // vertex_lookup[i] points to where the first vertex of block[i] is in vertex vector
        // really important for world editing
        std::vector<uint32_t> vertex_lookup;

        std::vector<uint32_t> indices;
        // index_lookup[i] points to where the first index of block[i] is in index vector
        // also important for world editing
        std::vector<uint32_t> index_lookup;

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
    };
}
