#pragma once

#include <glad.h>
#include <glm/mat4x4.hpp>

struct Shader {
  GLuint ID; // read-only. Should not be changed.

  Shader(); // default constructor
  Shader(const char* vertsrc, const char* fragsrc);
  ~Shader();

  void build(const char* vertsrc, const char* fragsrc);
  void build_from_files(const char* vertpath, const char* fragpath);

  void set_mat4(const glm::mat4& mat, const char* name);
  void set_tex_slot(GLuint slot, const char* name);
};
