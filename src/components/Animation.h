//
//  Author: Shervin Aflatooni
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "../EntityComponent.h"

class Animation : public EntityComponent
{
public:
  virtual ~Animation(void);

  void addPosition(glm::vec3 position);
  void addRotation(glm::quat rotation);
  void addScale(glm::vec3 scale);

  void updateFrameNumber(int frameNumber);
  virtual void registerWithEngine(Engine *engine);
  virtual void update(int delta);

private:
  std::vector<glm::vec3> positions;
  std::vector<glm::quat> rotations;
  std::vector<glm::vec3> scales;

protected:
  int currentFrame = 0;
  int previousFrame = 0;
};

#endif
