#version 330

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 fragColor;

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

  vec4 diffuseColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
  vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

  if (diffuseFactor > 0)
  {
    diffuseColor = vec4(base.color, 1.0f) * base.intensity * diffuseFactor;

    vec3 directionToEye = normalize(eyePos - worldPos0);
    vec3 reflectDirection = normalize(reflect(direction, normal));

    float specularFactor = dot(directionToEye, reflectDirection);
    specularFactor = pow(specularFactor, specularPower);

    if (specularFactor > 0)
    {
      specularColor = vec4(base.color, 1.0f) * specularIntensity * specularFactor;
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
  fragColor = texture(diffuse, texCoord0) * calculateDirectionalLight(directionalLight, normalize(normal0));
}
