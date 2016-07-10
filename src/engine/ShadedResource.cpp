//
//  Author: Shervin Aflatooni
//

#include "ShadedResource.h"

ShadedResource::ShadedResource(void)
{
  m_referenceCount = 0;
}

void ShadedResource::incrementReference(void)
{
  m_referenceCount++;
}

void ShadedResource::decrementReference(void)
{
  m_referenceCount--;

  if (m_referenceCount <= 0)
    delete this;
}
