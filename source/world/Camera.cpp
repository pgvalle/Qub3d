#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
  position = { 0, 0, 0 };
  yaw = 0;
  pitch = 0;
  // actual initialization of view, yaw and pitch
  rotate(-90, 0);
}

const glm::mat4& Camera::getViewMatrix() const {
  return view;
}

void Camera::rotate(float yawOff, float pitchOff) {
  yaw += glm::radians(yawOff);
  pitch -= glm::radians(pitchOff);

  // If we don't do this the view matrix will get messed up
  const float maxAbsPitchRad = glm::radians(MAX_ABS_PITCH);
  if (pitch >= maxAbsPitchRad) {
    pitch = maxAbsPitchRad;
  } else if (pitch <= -maxAbsPitchRad) {
    pitch = -maxAbsPitchRad;
  }

  const glm::vec3 direction = {
    glm::cos(yaw) * glm::cos(pitch),
    glm::sin(pitch),
    glm::sin(yaw) * glm::cos(pitch)
  };
  view = glm::lookAt(position, position + direction, UP);
}

void Camera::move(float xVel, float yVel, float zVel) {
  view = glm::translate(view, position);

  const glm::vec3 front = { -view[0][2], 0, -view[2][2] };
  position += xVel * glm::normalize(front);

  position += yVel * UP;

  const glm::vec3 right = { view[0][0], view[1][0], view[2][0] };
  position += zVel * right;

  view = glm::translate(view, -position);
}
