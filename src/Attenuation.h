//
//  Author: Shervin Aflatooni
//

#ifndef ATTENUATION_H
#define ATTENUATION_H

class Attenuation
{
public:
  Attenuation(float constant, float linear, float exponent);

  float getConstant(void);
  float getLinear(void);
  float getExponent(void);

private:
  float m_constant;
  float m_linear;
  float m_exponent;
};

#endif
