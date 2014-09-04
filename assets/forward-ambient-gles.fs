precision mediump float;

varying vec2 texCoord0;

uniform vec3 ambientIntensity;
uniform sampler2D diffuse;

void main()
{
  gl_FragColor = texture2D(diffuse, texCoord0) * vec4(ambientIntensity, 1.0);
}
