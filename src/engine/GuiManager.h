#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Window.h"
#include "TextureData.h"

class GuiManager
{
public:
  GuiManager(Window *window);
  ~GuiManager(void);

  void render(void);
  void tick(void);

private:
  SDL_Window *m_sdlWindow;
  Window *m_window;
  // TextureData *m_textureData;
};

#endif
