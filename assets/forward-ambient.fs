#version 330

in  vec2 texCoord0;
out vec4 fragColor;

uniform vec3 ambientIntensity;
uniform sampler2D diffuse;

void main()
{
  fragColor = texture(diffuse, texCoord0) * vec4(ambientIntensity, 1.0f);
}
