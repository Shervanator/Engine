#ifndef GAME_H
#define GAME_H

#include "SceneNode.h"

class Game
{
public:
  Game(void);
  virtual ~Game(void);

  virtual void init(void);

  void update(int delta);
  void render(void);

  SceneNode *getRootScene(void) { return &rootScene; };

protected:
  void addToScene(SceneNode *node);

private:
  SceneNode rootScene;
};

#endif
