#include "block.h"

namespace qub3d
{
    /*
    Reminder!!!
    Vertex order:
      1. right
      2. top
      3. front
      4. left
      5. bottom
      6. back
    */

    const Vertex* get_block_default_mesh(BlockId id)
    {
        static Vertex mesh[24] = {
             // right
             0.5f, -0.5f,  0.5f,   0, 0,
             0.5f, -0.5f, -0.5f,   0, 1,
             0.5f,  0.5f, -0.5f,   1, 1,
             0.5f,  0.5f,  0.5f,   1, 0,

             // top
             0.5f,  0.5f, -0.5f,   0, 0,
            -0.5f,  0.5f, -0.5f,   0, 1,
            -0.5f,  0.5f,  0.5f,   1, 1,
             0.5f,  0.5f,  0.5f,   1, 0,

             // front
            -0.5f, -0.5f,  0.5f,   0, 0,
             0.5f, -0.5f,  0.5f,   0, 1,
             0.5f,  0.5f,  0.5f,   1, 1,
            -0.5f,  0.5f,  0.5f,   1, 0,

             // left
            -0.5f, -0.5f,  0.5f,   0, 0,
            -0.5f,  0.5f,  0.5f,   0, 1,
            -0.5f,  0.5f, -0.5f,   1, 1,
            -0.5f, -0.5f, -0.5f,   1, 0,

             // bottom
             0.5f, -0.5f, -0.5f,   0, 0,
             0.5f, -0.5f,  0.5f,   0, 1,
            -0.5f, -0.5f,  0.5f,   1, 1,
            -0.5f, -0.5f, -0.5f,   1, 0,

             // back
            -0.5f, -0.5f, -0.5f,   0, 0,
            -0.5f,  0.5f, -0.5f,   0, 1,
             0.5f,  0.5f, -0.5f,   1, 1,
             0.5f, -0.5f, -0.5f,   1, 0,
        };

        return mesh;
    }
}