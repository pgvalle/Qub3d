#pragma once

#include <glad.h>
#include <linmath.h>

GLuint qub3d_build_shader(const char* vert_src, const char* frag_src, const char* name);
void qub3d_set_shader_mat4(GLuint shader, const char* name, const mat4x4 mat);
