//
//  Author: Shervin Aflatooni
//

#ifndef SHARED_RESOURCE
#define SHARED_RESOURCE

class ShadedResource
{
public:
  ShadedResource(void);
  virtual ~ShadedResource(void) {};

  void incrementReference(void);
  void decrementReference(void);

private:
  int m_referenceCount;
};

#endif
