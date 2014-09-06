#include "Attenuation.h"

Attenuation::Attenuation(float constant, float linear, float exponent)
{
  m_constant = constant;
  m_linear = linear;
  m_exponent = exponent;
}

float Attenuation::getConstant(void)
{
  return m_constant;
}

float Attenuation::getLinear(void)
{
  return m_linear;
}

float Attenuation::getExponent(void)
{
  return m_exponent;
}
