#pragma once

#include <glad.h>
#include <linmath.h>

namespace qub3d
{
    GLuint build_shader(const char* vert_src, const char* frag_src, const char* name);
    void set_shader_mat4(GLuint shader, const mat4x4 mat, const char* name);
}
