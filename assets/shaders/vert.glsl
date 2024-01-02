#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvs_;

out vec2 uvs;

uniform mat4 proj;
uniform mat4 view;

void main() {
  gl_Position = proj * view * vec4(pos, 1.0);
  uvs = uvs_;
}
  