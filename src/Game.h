#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "GLManager.h"
#include "Input.h"

class Engine;

class Game
{
public:
  Game(void);
  virtual ~Game(void);

  void setEngine(Engine *engine);

  virtual void init(void);

  virtual void updateInput(Input *input, int delta);
  virtual void update(int delta);
  virtual void render(GLManager *glManager);

  Entity *getRootScene(void) { return &rootScene; };

protected:
  void addToScene(Entity *entity);
  Engine *getEngine(void);

private:
  Entity rootScene;
  Engine *engine;
};

#endif
