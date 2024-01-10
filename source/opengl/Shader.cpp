#include "Shader.h"

#include <cstdio>
#include <cstdlib>

Shader::Shader() {
  id = 0;
}

Shader::~Shader() {
  if (id) {
    glDeleteProgram(id);
  }
}


void Shader::compile(const char* vshSrc, const char* fshSrc) {
  if (id) {
    printf("Shader info: Already compiled!\n");
    return;
  }

  int success;
  char info[1024];

  GLuint vsh = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vsh, 1, &vshSrc, 0);
  glCompileShader(vsh);

  glGetShaderiv(vsh, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vsh, 1024, nullptr, info);
    printf("Vertex shader info:\n%s\n%s", vshSrc, info);
    exit(-1);
  }

  GLuint fsh = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fsh, 1, &fshSrc, 0);
  glCompileShader(fsh);

  glGetShaderiv(fsh, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fsh, 1024, nullptr, info);
    printf("Fragment shader info:\n%s\n%s", fshSrc, info);
    exit(-1);
  }

  id = glCreateProgram();
  glAttachShader(id, vsh);
  glAttachShader(id, fsh);
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 1024, nullptr, info);
    printf("Shader program info:\n%s", info);
    exit(-1);
  }

  // Shaders were compiled, linked and sent to gpu. We don't need these anymore.
  glDeleteShader(vsh);
  glDeleteShader(fsh);
}

void Shader::compileFromPaths(const char* vshPath, const char* fshPath) {
  FILE* vshFile = fopen(vshPath, "r");
  if (vshFile == NULL) {
    printf("Shader info: could not load file %s\n", vshPath);
    exit(-1);
  }

  fseek(vshFile, 0, SEEK_END);
  size_t vshFileLen = ftell(vshFile);
  fseek(vshFile, 0, SEEK_SET);

  char* vshSrc = new char[vshFileLen + 1]{ 0 };
  fread(vshSrc, 1, vshFileLen, vshFile);
  fclose(vshFile);

  FILE* fshFile = fopen(fshPath, "r");
  if (fshFile == NULL) {
    printf("Shader info: could not load file %s\n", fshPath);
    exit(-1);
  }

  fseek(fshFile, 0, SEEK_END);
  size_t fshFileLen = ftell(fshFile);
  fseek(fshFile, 0, SEEK_SET); 

  char* fshSrc = new char[fshFileLen + 1]{ 0 };
  fread(fshSrc, 1, fshFileLen, fshFile);
  fclose(fshFile);

  compile(vshSrc, fshSrc);

  // don't keep them loaded in memory
  delete[] vshSrc, fshSrc;
}

void Shader::use() const {
  glUseProgram(id);
}

void Shader::uploadMat4(const char* name, const glm::mat4& mat) const {
  const GLint location = glGetUniformLocation(id, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::uploadUInt(const char* name, GLuint value) const {
  const GLint location = glGetUniformLocation(id, name);
  glUniform1ui(location, value);
}
