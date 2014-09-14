precision mediump float;

varying vec2 texCoord0;
varying vec3 worldPos0;
varying mat3 tbnMatrix;

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

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

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
      specularColor = vec4(base.color, 1.0) * (texture2D(specularMap, texCoord0).r * specularFactor);
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
  vec3 normal = normalize(tbnMatrix * (255.0/128.0 * texture2D(normalMap, texCoord0).xyz - vec3(1, 1, 1)));
  gl_FragColor = texture2D(diffuseMap, texCoord0) * calculateDirectionalLight(directionalLight, normal);
}
