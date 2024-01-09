#pragma once

#include <glad.h>
#include <glm/mat4x4.hpp>

class Shader {
private:
  GLuint id; // read-only. Should not be changed.
  
public:
  Shader();
  ~Shader();

  void use() const;

  void compile(const char* vshSrc, const char* fshSrc);
  void compileFromPaths(const char* vshPath, const char* fshPath);

  void uploadMat4(const char* name, const glm::mat4& mat) const;
  void uploadUInt(const char* name, GLuint value) const;
};
