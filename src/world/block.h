#pragma once

#include <cstdint>
#include <linmath.h>

namespace qub3d
{
    typedef uint16_t BlockId;

    struct Vertex
    {
        vec3 position;
        vec2 uv;
    };

    /*
    The value returned is the original one!!!
    Return the default block mesh as if all faces are being shown when rendering.
    If that's not the case we'll treat which faces should when building chunk mesh.
    Vertex order:
      1. right
      2. top
      3. front
      4. left
      5. bottom
      6. back
    */
    Vertex* get_block_default_mesh(BlockId id);
}