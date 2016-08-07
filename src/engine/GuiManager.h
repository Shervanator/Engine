#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Window.h"
#include "Entity.h"

class GuiManager
{
public:
  GuiManager(Window *window);
  ~GuiManager(void);

  void render(Entity *sceneGraph);
  void tick(void);

private:
  SDL_Window *m_sdlWindow;
  Window *m_window;
};

#endif
