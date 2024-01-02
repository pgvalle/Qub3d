#include "camera.h"
#include <cmath>


static const glm::vec3 UP = { 0, 1, 0 };

Camera::Camera() {
  pos = { 0, 0, 0 };
  yaw = 0;
  pitch = 0;
  sensitivity = 0.5;
  // setup view
  rotate(0, 0);
}


const glm::mat4* Camera::view_mat() const {
  return &view;
}

// TODO: Integrate me with glm!

void Camera::rotate(float yawoff, float pitchoff) {
  yaw += sensitivity * yawoff;
  pitch -= sensitivity * pitchoff;

  // Prevent players of breaking their necks LOL.
  // direction and up can't be parallel. It would mess up the view matrix.
  if (pitch >= 89.9f) {
    pitch = 89.9f; // 90 or -90 means direction and up are parallel.
  } else if (pitch <= -89.9f) {
    pitch = -89.9f;
  }

  // PI/180 = 0.01745329251
  const float yaw_rad = 0.01745329251f * yaw;
  const float pitch_rad = 0.01745329251f * pitch;

  const glm::vec3 direction = {
    cosf(yaw_rad) * cosf(pitch_rad),
    sinf(pitch_rad),
    sinf(yaw_rad) * cosf(pitch_rad)
  };
  glm::vec3 center = pos + direction;

  glm::lookAt
  //mat4x4_look_at(view, pos, center, UP);
}

void Camera::move(float xvel, float yvel, float zvel) {
  // mat4x4_translate_in_place(view, pos[0], pos[1], pos[2]);

  // // para a frente/trás relativo do player
  // vec3 front = { -view[0][2], 0, -view[2][2] };
  // vec3_scale(front, front, xvel / vec3_len(front));
  // vec3_add(pos, pos, front);

  // // para cima/baixo absoluto do mundo
  // vec3 up;
  // vec3_scale(up, UP, yvel);
  // vec3_add(pos, pos, up);

  // // para a direita/exquerda relativa do player
  // vec3 right = { view[0][0], view[1][0], view[2][0] };
  // vec3_scale(right, right, zvel);
  // vec3_add(pos, pos, right);

  // mat4x4_translate_in_place(view, -pos[0], -pos[1], -pos[2]);
}
