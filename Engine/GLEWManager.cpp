#include <iostream>
#include <GL/glew.h>

#include "GLEWManager.h"

GLEWManager::GLEWManager(void)
{
}

GLEWManager::~GLEWManager(void)
{
}

void GLEWManager::clean(void)
{
}

int GLEWManager::init(void)
{
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (GLEW_OK != err)
  {
    std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    return 1;
  }

  std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  return 0;
}
