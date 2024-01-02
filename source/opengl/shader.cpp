#include "shader.h"

#include <cstdio>
#include <cstdlib>


Shader::Shader() {
  ID = 0;
}

Shader::Shader(const char* vertsrc, const char* fragsrc) {
  build(vertsrc, fragsrc);
}

Shader::~Shader() {
  if (ID) {
    glDeleteProgram(ID);
  }
}


void Shader::build(const char* vertsrc, const char* fragsrc) {
  // don't redo the thing
  if (ID != 0) {
    return;
  }

  int success;
  char info[1024];

  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vertsrc, 0);
  glCompileShader(vert);

  glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert, 1024, nullptr, info);
    printf("Vertex shader info:\n%s\n%s", vertsrc, info);
    exit(-1);
  }

  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &fragsrc, 0);
  glCompileShader(frag);

  glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frag, 1024, nullptr, info);
    printf("Fragment shader info:\n%s\n%s", fragsrc, info);
    exit(-1);
  }

  ID = glCreateProgram();
  glAttachShader(ID, vert);
  glAttachShader(ID, frag);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 1024, nullptr, info);
    printf("Shader program info:\n%s", info);
    exit(-1);
  }

  // Shaders were copied and linked together in program.
  // We don't need them anymore.
  glDeleteShader(vert);
  glDeleteShader(frag);
}

void Shader::build_from_files(const char* vertpath, const char* fragpath) {
  // try reading files

  FILE* vertfile = fopen(vertpath, "r");
  if (vertfile == NULL) {
    printf("Shader info: could not load file %s\n", vertpath);
    exit(-1);
  }

  FILE* fragfile = fopen(fragpath, "r");
  if (fragfile == NULL) {
    printf("Shader info: could not load file %s\n", fragpath);
    exit(-1);
  }

  // get file sizes

  fseek(vertfile, 0, SEEK_END);
  size_t len_vertfile = ftell(vertfile);
  fseek(vertfile, 0, SEEK_SET); // go back to read

  fseek(fragfile, 0, SEEK_END);
  size_t len_fragfile = ftell(fragfile);
  fseek(fragfile, 0, SEEK_SET);

  // read files' contents

  char* vertsrc = new char[len_vertfile + 1]{ 0 };
  fread(vertsrc, 1, len_vertfile, vertfile);
  fclose(vertfile);

  char* fragsrc = new char[len_fragfile + 1]{ 0 };
  fread(fragsrc, 1, len_fragfile, fragfile);
  fclose(fragfile);

  build(vertsrc, fragsrc);

  // don't keep them loaded in memory
  delete[] vertsrc, fragsrc;
}


void Shader::set_mat4(const mat4x4 mat, const char* name) {
  const GLint location = glGetUniformLocation(ID, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_tex_slot(GLuint slot, const char* name) {
  const GLint location = glGetUniformLocation(ID, name);
  glUniform1ui(location, slot);
}
