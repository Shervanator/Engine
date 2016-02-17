precision mediump float;

varying vec2 texCoord0;

uniform vec3 ambientIntensity;
uniform sampler2D diffuse;

void main()
{
  vec4 texel = texture2D(diffuse, texCoord0);
  if(texel.a < 0.5)
    discard;
  gl_FragColor = texel * vec4(ambientIntensity, 1.0);
}
