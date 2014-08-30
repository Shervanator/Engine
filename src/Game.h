#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "GLManager.h"
#include "KeyboardHandler.h"

class Game
{
public:
  Game(void);
  virtual ~Game(void);

  virtual void init(void);

  virtual void update(int delta, KeyboardHandler *keyboardHandler);
  virtual void render(GLManager *glManager);

  Entity *getRootScene(void) { return &rootScene; };

protected:
  void addToScene(Entity *entity);

private:
  Entity rootScene;
};

#endif
