#version 330 core

uniform sampler2D tex;

in vec2 uvs;

out vec4 color;

void main() {
  color = vec4(uvs, 1.0, 1.0);
}
