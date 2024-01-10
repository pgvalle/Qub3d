#pragma once

#include <glm/glm.hpp>

class Camera {
private:
  static constexpr glm::vec3 UP = { 0, 1, 0 };
  static constexpr float MAX_ABS_PITCH = 89.99f;

  glm::vec3 position;
  glm::mat4 view;
  float yaw, pitch;

public:
  Camera();

  const glm::mat4& getViewMatrix() const;

  void rotate(float yawOff, float pitchOff);
  void move(float xVel, float yVel, float zVel);
};
