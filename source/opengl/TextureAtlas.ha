#pragma once

#include <map>
#include <string>

#include <glad.h>
#include <glm/vec2.hpp>

class TextureAtlas {
private:
  GLuint id;
  GLenum slot;
  // map image filename to it's position inside atlas
  std::map<std::string, glm::vec2> name2rect;

public:
  TextureAtlas();
  ~TextureAtlas();

  // slot 0 is reserved for unbinding texture slot
  void build_from_files(const char* dirname, GLenum slot);

  GLenum get_slot() const {
    return slot;
  }

  glm::vec2 mapped_uv(const char* name, const glm::vec2& v) const;
};