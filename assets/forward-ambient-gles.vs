attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 ViewProj;
uniform mat4 World;

void main()
{
  gl_Position = ViewProj * World * vec4(position, 1.0);
  texCoord0 = texCoord;
}
