//
//  Author: Shervin Aflatooni
//

#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "GLManager.h"
#include "Input.h"
#include <vector>

class Engine;

class Game
{
public:
  Game(void);
  virtual ~Game(void);

  void setEngine(Engine *engine);

  virtual void init(GLManager *glManager);

  virtual void updateInput(Input *input, int delta);
  virtual void update(int delta);
  virtual void render(GLManager *glManager);

  Entity *getRootScene(void) { return scenes[0]; };

protected:
  void addToScene(Entity *entity, int sceneIndex = 0);
  Engine *getEngine(void);

private:
  std::vector<Entity*> scenes;
  Engine *engine;
};

#endif
