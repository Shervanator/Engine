#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "Window.h"
#include "Entity.h"

#include <imgui.h>

class GuiManager
{
public:
  GuiManager(Window *window);
  ~GuiManager(void);

  void render(Entity *sceneGraph);
  void tick(void);

  void addInputCharactersUTF8(const char *text);
  void setKeyEvent(int key, bool keydown);

  void togglePropertyEditor(void);

private:
  void createDeviceObjects(void);
  void invalidateDeviceObjects(void);
  static void renderDrawLists(ImDrawData* draw_data);

  bool showProps;

  SDL_Window *m_sdlWindow;
  Window *m_window;
};

#endif
