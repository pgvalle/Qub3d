#pragma once

#include <linmath.h>

class Camera {
private:
  vec3 pos = { 0, 0, 0, };
  float yaw = 0, pitch = 0;
  float sensitivity = 0.5f;
  mat4x4 view;

public:
  Camera() {
    rotate(0, 0);
  }

  const vec4* view_mat() const {
    return &view[0];
  }

  void rotate(float yawoff, float pitchoff);
  // x, y and z in camera space.
  // x: forward(+) or back(-)
  // y: up(+) or down(-)
  // z: right(+) or left(-)
  void move(float xvel, float yvel, float zvel);
};
