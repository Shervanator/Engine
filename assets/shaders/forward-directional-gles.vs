attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 tangent;

varying vec2 texCoord0;
varying vec3 worldPos0;
varying mat3 tbnMatrix;

uniform mat4 View;
uniform mat4 Proj;
uniform mat4 World;

void main()
{
  gl_Position = Proj * View * World * vec4(position, 1.0);
  texCoord0 = texCoord;
  worldPos0 = (World * vec4(position, 1.0)).xyz;

  vec3 n = normalize((World * vec4(normal, 0.0)).xyz);
  vec3 t = normalize((World * vec4(tangent, 0.0)).xyz);
  t = normalize(t - dot(t, n) * n);

  vec3 biTangent = cross(t, n);
  tbnMatrix = mat3(t, biTangent, n);
}
