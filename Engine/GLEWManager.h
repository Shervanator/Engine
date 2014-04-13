#ifndef GLEW_MANAGER_H
#define GLEW_MANAGER_H

class GLEWManager
{
public:
  GLEWManager(void);
  ~GLEWManager(void);

  void clean(void);

  int init(void);

private:
};

#endif
