//
//  Author: Shervin Aflatooni
//

#ifndef ATTENUATION_H
#define ATTENUATION_H

class Attenuation
{
public:
  Attenuation(float constant, float linear, float exponent);

  float getConstant(void) const;
  float getLinear(void) const;
  float getExponent(void) const;

// private:
  float m_constant;
  float m_linear;
  float m_exponent;
};

#endif
