#version 330

in  vec2 texCoord0;
out vec4 fragColor;

uniform vec3 ambientIntensity;

uniform sampler2D diffuseMap;

void main()
{
  fragColor = texture(diffuseMap, texCoord0) * vec4(ambientIntensity, 1.0f);
}
