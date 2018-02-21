//
//  Author: Shervin Aflatooni
//

#pragma once

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

  virtual void init(GLManager *glManager);

  virtual void update(Input *input, std::chrono::microseconds delta);
  virtual void render(GLManager *glManager);

  inline std::shared_ptr<Entity> getRootScene(void) { return rootScene; };

protected:
  void addToScene(std::shared_ptr<Entity> entity);
  Engine *getEngine(void) const;

private:
  std::shared_ptr<Entity> rootScene;
  Engine *engine;
};
