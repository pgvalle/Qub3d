#include "TextureAtlas.h"

#include <filesystem>
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


namespace fs = std::filesystem;


TextureAtlas::TextureAtlas() {
  id = 0;
  slot = 0;
}

TextureAtlas::~TextureAtlas() {
  // TODO: Implement proper destructor to TextureAtlas
}


void TextureAtlas::build_from_files(const char* dirname, GLenum slot) {
  // must be a directory
  if (!fs::is_directory(dirname)) {
    return;
  }
  
  // counting how many images we have (acounting placeholder)
  int imgs = 1;
  for (const fs::directory_entry& entry : fs::directory_iterator(dirname)) {
    // ignore directories and non-png files
    if (!entry.is_directory() && entry.path().extension() == ".png") {
      imgs++;
    }
  }

  // calculate best possible atlas size so that we don't waste memory

  const int rows = ceilf(sqrtf(imgs));
  const int cols = ceilf((float)imgs / rows);
  const int width = img_dim * rows; // pixels
  const int height = img_dim * cols; // pixels

  uint32_t* atlas = new uint32_t[width * height](0)
}


glm::vec2 TextureAtlas::mapped_uv(const char* name, const glm::vec2& v) const {
  return {};
}


// void TextureAtlas::set_image(int width, int height, void* data, int tex_size, GLenum slot_) {
//   if (id != 0) { // only set image once
//     return;
//   }

//   // setting fields
//   glGenTextures(1, &id);
//   slot = slot_;
//   texx = float(tex_size) / width;
//   texy = float(tex_size) / height;

//   // binding texture to slot
//   glActiveTexture(slot);
//   // configuring texture slot
//   glBindTexture(GL_TEXTURE_2D, id);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);   
//   // sending data to slot
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//   glGenerateMipmap(GL_TEXTURE_2D);

//   glActiveTexture(GL_TEXTURE0); // unbind texture slot
// }


// void TextureAtlas::add_entry(const std::string& name, float x, float y) {
//   name2vec.insert(std::pair<std::string, glm::vec2>(name, { x, y }));
// }
