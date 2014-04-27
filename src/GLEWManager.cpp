#include <iostream>
#include <GL/glew.h>

#include "GLEWManager.h"

GLEWManager::GLEWManager(void)
{
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (GLEW_OK != err)
  {
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
  }

  std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
}

GLEWManager::~GLEWManager(void)
{
}
