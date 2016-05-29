//
//  Author: Shervin Aflatooni
//

#ifndef VIDEO_ANIMATION_H
#define VIDEO_ANIMATION_H

#include "Animation.h"
#include "../TextureData.h"
#include "../EntityComponent.h"
#include "../Video.h"

class VideoAnimation : public Animation
{
public:
  VideoAnimation(TextureData *textureData, Video *video);
  virtual ~VideoAnimation(void);
  virtual void update(int delta);

private:
  TextureData *textureData;
  Video *video;
};

#endif
