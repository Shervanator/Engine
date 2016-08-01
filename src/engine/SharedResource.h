//
//  Author: Shervin Aflatooni
//

#ifndef SHARED_RESOURCE
#define SHARED_RESOURCE

class SharedResource
{
public:
  SharedResource(void);
  virtual ~SharedResource(void) {};

  void incrementReference(void);
  void decrementReference(void);

private:
  int m_referenceCount;
};

#endif
