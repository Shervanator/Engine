#include <iostream>

#ifndef EMSCRIPTEN
  #include <GL/glew.h>
#endif

#include "GLEWManager.h"

GLEWManager::GLEWManager(void)
{
#ifndef EMSCRIPTEN
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (GLEW_OK != err)
  {
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
  }

  std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
#endif
}

GLEWManager::~GLEWManager(void)
{
}
