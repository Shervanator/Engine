precision mediump float;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;

struct BaseLight
{
  vec3 color;
  float intensity;
};

struct DirectionalLight
{
  BaseLight base;
  vec3 direction;
};

uniform vec3 eyePos;
uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;

uniform sampler2D diffuse;

vec4 calculateLight(BaseLight base, vec3 direction, vec3 normal)
{
  float diffuseFactor = dot(normal, -direction);

  vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 0.0);
  vec4 specularColor = vec4(0.0, 0.0, 0.0, 0.0);

  if (diffuseFactor > 0.0)
  {
    diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;

    vec3 directionToEye = normalize(eyePos - worldPos0);
    vec3 reflectDirection = normalize(reflect(direction, normal));

    float specularFactor = dot(directionToEye, reflectDirection);
    specularFactor = pow(specularFactor, specularPower);

    if (specularFactor >  0.0)
    {
      specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor;
    }
  }

  return diffuseColor + specularColor;
}

vec4 calculateDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
  return calculateLight(directionalLight.base, directionalLight.direction, normal);
}

void main()
{
  gl_FragColor = texture2D(diffuse, texCoord0) * calculateDirectionalLight(directionalLight, normalize(normal0));
}
