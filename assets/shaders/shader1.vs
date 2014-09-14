#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 UV;

uniform mat4 ViewProj;
uniform mat4 World;

void main() {
  gl_Position = ViewProj * World * vec4(position, 1.0);
  UV = texCoord;
}
