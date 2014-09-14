#version 330

in vec2 texCoord0;
in vec3 worldPos0;
in mat3 tbnMatrix;

out vec4 fragColor;

struct BaseLight
{
  vec3 color;
  float intensity;
};

struct Attenuation
{
  float constant;
  float linear;
  float exponent;
};

struct PointLight
{
  BaseLight base;
  Attenuation attenuation;
  vec3 position;
  float range;
};

uniform vec3 eyePos;
uniform float specularIntensity;
uniform float specularPower;

uniform PointLight pointLight;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

vec4 calculateLight(BaseLight base, vec3 direction, vec3 normal)
{
  float diffuseFactor = dot(normal, -direction);

  vec4 diffuseColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
  vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

  if (diffuseFactor > 0.0f)
  {
    diffuseColor = vec4(base.color, 1.0f) * base.intensity * diffuseFactor;

    vec3 directionToEye = normalize(eyePos - worldPos0);
    vec3 reflectDirection = normalize(reflect(direction, normal));

    float specularFactor = dot(directionToEye, reflectDirection);
    specularFactor = pow(specularFactor, specularPower);

    if (specularFactor > 0.0f)
    {
      specularColor = vec4(base.color, 1.0f) * (texture(specularMap, texCoord0).r * specularFactor);
    }
  }

  return diffuseColor + specularColor;
}

vec4 calculatePointLight(PointLight pointLight, vec3 normal)
{
  vec3 lightDirection = worldPos0 - pointLight.position;
  float distanceToPoint = length(lightDirection);

  if (distanceToPoint > pointLight.range)
    return vec4(0, 0, 0, 0);

  lightDirection = normalize(lightDirection);

  vec4 color = calculateLight(pointLight.base, lightDirection, normal);

  float attenuation = pointLight.attenuation.constant
                      + pointLight.attenuation.linear * distanceToPoint
                      + pointLight.attenuation.exponent * distanceToPoint * distanceToPoint
                      + 0.0001;

  return color / attenuation;
}

void main()
{
  vec3 normal = normalize(tbnMatrix * (255.0/128.0 * texture(normalMap, texCoord0).xyz - 1));
  fragColor = texture(diffuseMap, texCoord0) * calculatePointLight(pointLight, normal);
}
