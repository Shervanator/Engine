#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 View;
uniform mat4 Proj;
uniform mat4 World;

void main()
{
  gl_Position = Proj * View * World * vec4(position, 1.0);
  texCoord0 = texCoord;
}
