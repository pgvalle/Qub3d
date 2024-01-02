#include "camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>


static const glm::vec3 UP = { 0, 1, 0 };

Camera::Camera() {
  pos = { 0, 0, 0 };
  yaw = 0;
  pitch = 0;
  sensitivity = 0.5;
  // setup view
  rotate(0, 0);
}


const glm::mat4& Camera::view_mat() const {
  return view;
}


void Camera::rotate(float yawoff, float pitchoff) {
  yaw += sensitivity * yawoff;
  pitch -= sensitivity * pitchoff;

  // Prevent players of breaking their necks LOL.
  // direction and up can't be parallel. It would mess up the view matrix.
  if (pitch >= 89.99f) {
    pitch = 89.99f; // 90 or -90 means direction and up are parallel.
  } else if (pitch <= -89.99f) {
    pitch = -89.99f;
  }

  // PI/180 = 0.01745329251
  const float yaw_rad = 0.01745329251f * yaw;
  const float pitch_rad = 0.01745329251f * pitch;

  const glm::vec3 direction = {
    cosf(yaw_rad) * cosf(pitch_rad),
    sinf(pitch_rad),
    sinf(yaw_rad) * cosf(pitch_rad)
  };
  view = glm::lookAt(pos, pos + direction, UP);
}

void Camera::move(float xvel, float yvel, float zvel) {
  view = glm::translate(view, pos);

  // para a frente/trás relativo do player
  const glm::vec3 front = { -view[0][2], 0, -view[2][2] };
  pos += xvel * glm::normalize(front);

  // para cima/baixo absoluto do mundo
  pos += yvel * UP;

  // para a direita/exquerda relativa do player
  const glm::vec3 right = { view[0][0], view[1][0], view[2][0] };
  pos += zvel * right;

  view = glm::translate(view, -pos);
}
