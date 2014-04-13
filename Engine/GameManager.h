#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "GLManager.h"
#include "SDLManager.h"
#include "GLEWManager.h"

#include "Camera.h"

class GameManager
{
public:
  GameManager(void);
  ~GameManager(void);

  int init(const int width, const int height);
  void tick(void);
  void clean(void);
  bool shouldQuit(void);
private:
  SDLManager  sdl_manager;
  GLEWManager glew_manager;
  GLManager   gl_manager;

  Camera *primary_camera;

  int WIDTH;
  int HEIGHT;

  bool quit;
};

#endif
