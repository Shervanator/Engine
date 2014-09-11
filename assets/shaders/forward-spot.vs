#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;

uniform mat4 ViewProj;
uniform mat4 World;

void main()
{
  gl_Position = ViewProj * World * vec4(position, 1.0);
  texCoord0 = texCoord;
  normal0 = (World * vec4(normal, 0.0f)).xyz;
  worldPos0 = (World * vec4(position, 1.0f)).xyz;
}
