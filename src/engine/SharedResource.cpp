//
//  Author: Shervin Aflatooni
//

#include "SharedResource.h"

SharedResource::SharedResource(void)
{
  m_referenceCount = 0;
}

void SharedResource::incrementReference(void)
{
  m_referenceCount++;
}

void SharedResource::decrementReference(void)
{
  m_referenceCount--;

  if (m_referenceCount <= 0)
    delete this;
}
