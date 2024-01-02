#include "Internal.h"
#include <cmath>
#include <filesystem>

#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


namespace fs = std::filesystem;

int count_pngs(const char* path) {
  int pngs = 0;
  for (const auto& entry : fs::directory_iterator(path)) {
    if (entry.path().extension() == ".png") {
      pngs++;
    }
  }
  return pngs;
}

uint32_t* gen_fallback_texture(int dim) {
  uint32_t* fallback = new uint32_t[dim * dim];
  uint32_t color = 0xfff800f8; // purple
  for (int i = 0; i < dim; i++) {
    if (i != dim >> 1) {
      color = (color == 0xff000000 ? 0xfff800f8 : 0xff000000);
    }
    for (int j = 0; j < dim; j++) {
      if (j == dim >> 1) {
        color = (color == 0xff000000 ? 0xfff800f8 : 0xff000000);
      }
      fallback[j + dim * i] = color;
    }
  }
  return fallback;
}

void load_and_pack_textures() {
  stbi_set_flip_vertically_on_load(true);

  const char* path = "../../../assets/textures";
  const int img_dim = 16;

  const int imgs = count_pngs(path) + 1; // consider fallback texture as well

  // Calculate best possible atlas size so that we don't waste memory

  const int rows = ceilf(sqrtf(imgs));
  const int cols = ceilf((float)imgs / rows);
  const int w = img_dim * rows; // pixels
  const int h = img_dim * cols; // pixels

  // allocate atlas

  const int channels = sizeof(uint32_t);
  uint32_t* atlas = new uint32_t[w * h](0); // uint32_t = 4 channels

  // paste fallback inside atlas first

  uint32_t* fallback = gen_fallback_texture(img_dim);
  for (int i = 0; i < img_dim; i++) {
    memcpy(atlas + i * w, fallback + i * img_dim, channels * img_dim);
  }
  delete[] fallback;

  // read all images and put them in the atlas

  int idx = 1; // 0 is already reserved to fallback texture
  for (const auto& entry : fs::directory_iterator(path)) {
    const auto& epath = entry.path();
    if (epath.extension() != ".png") { // ignore non-png files
      continue;
    }

    // load the image

    int img_w, img_h;
    uint32_t* img = (uint32_t*)stbi_load(epath.string().c_str(),
      &img_w, &img_h, NULL, 4);

    assert(img_w == img_dim && img_h == img_dim); // safety check

    // paste image apropriately inside atlas

    const int offset = img_dim * w * (idx / rows) + img_dim * (idx % cols);
    for (int i = 0; i < img_dim; i++) {
      memcpy(atlas + i * w + offset, img + i * img_dim, channels * img_dim);
    }
    stbi_image_free(img);

    // map the texture to its uvs

    const auto name = epath.filename().replace_extension();
    //app.blocks_atlas_uvs[name.string()][0] = float(idx % cols) / cols;
    //app.blocks_atlas_uvs[name.string()][1] = 1 - float(idx / rows) / rows;

    idx++;
  }

  glGenTextures(1, &app.blocks_atlas_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, app.blocks_atlas_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, h, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas);
  glGenerateMipmap(GL_TEXTURE_2D);
  app.shader.set_tex_slot(0, "tex");

  delete[] atlas;
}
