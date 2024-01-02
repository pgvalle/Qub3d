#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
private:
  glm::vec3 pos;
  glm::mat4 view;
  float yaw, pitch;
  float sensitivity;

public:
  Camera();

  const glm::mat4& view_mat() const;

  void rotate(float yawoff, float pitchoff);
  // x and z in camera space.
  // x: forward(+) or back(-)
  // y: up(+) or down(-)
  // z: right(+) or left(-)
  void move(float xvel, float yvel, float zvel);
};
