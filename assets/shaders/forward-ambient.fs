#version 330

in  vec2 texCoord0;
out vec4 fragColor;

uniform vec3 ambientIntensity;

uniform sampler2D diffuseMap;

void main()
{
  vec4 texel = texture(diffuseMap, texCoord0);
  if(texel.a < 0.5)
    discard;
  fragColor = texel * vec4(ambientIntensity, 1.0f);
}
