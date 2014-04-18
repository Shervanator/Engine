#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "GLManager.h"
#include "SDLManager.h"
#include "GLEWManager.h"

#include "Camera.h"

#include "KeyboardHandler.h"

class GameManager
{
public:
  GameManager(int width, int height);
  ~GameManager(void);

  void tick(void);
  bool shouldQuit(void);
private:
  SDLManager  *sdl_manager;
  GLEWManager *glew_manager;
  GLManager   *gl_manager;

  KeyboardHandler keyHandler;

  Camera *primary_camera;

  bool quit;
};

#endif
