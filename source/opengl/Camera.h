#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
private:
  static const float MAX_ABS_PITCH = 89.99f;

  glm::vec3 position;
  glm::mat4 view;
  float yaw, pitch;

public:
  Camera();

  const glm::mat4& getViewMatrix() const;

  void rotate(float yawOff, float pitchOff);
  void move(float xVel, float yVel, float zVel);
};
