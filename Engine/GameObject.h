#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject
{
public:
  virtual ~GameObject(void) {};

  virtual void update(int delta) = 0;
  virtual void render(void) = 0;

private:
};

#endif
