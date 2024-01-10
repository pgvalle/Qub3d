#pragma once

#include <glad.h>
#include <glm/glm.hpp>

class Shader {
private:
  GLuint id;
  
public:
  Shader();
  ~Shader();

  void compile(const char* vshSrc, const char* fshSrc);
  void compileFromPaths(const char* vshPath, const char* fshPath);

  void use() const;

  void uploadMat4(const char* name, const glm::mat4& mat) const;
  void uploadUInt(const char* name, GLuint value) const;
};
