#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

static const glm::vec3 UP = { 0, 1, 0 };

Camera::Camera() {
  position = { 0, 0, 0 };
  yaw = 0;
  pitch = 0;
  // setup view
  rotate(0, 0);
}

const glm::mat4& Camera::getViewMatrix() const {
  return view;
}

void Camera::rotate(float yawOff, float pitchOff) {
  yaw += glm::radians(yawOff);
  pitch -= glm::radians(pitchOff);
  // direction and up can't be parallel. It would mess up the view matrix.
  if (pitch >= MAX_ABS_PITCH) {
    pitch = MAX_ABS_PITCH;
  } else if (pitch <= -MAX_ABS_PITCH) {
    pitch = -MAX_ABS_PITCH;
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

  // para a frente/tras relativo ao player
  const glm::vec3 front = { -view[0][2], 0, -view[2][2] };
  position += xVel * glm::normalize(front);

  // para cima/baixo absoluto do mundo
  position += yVel * UP;

  // para a direita/exquerda relativa do player
  const glm::vec3 right = { view[0][0], view[1][0], view[2][0] };
  position += zVel * right;

  view = glm::translate(view, -position);
}
