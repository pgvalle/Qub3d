#version 330 core

uniform sampler2D tex;

in vec2 uvs;

out vec4 color;

void main() {
  color = texture(tex, uvs);
}
