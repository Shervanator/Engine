//
//  Author: Shervin Aflatooni
//

#include "VideoAnimation.h"

#include "../Engine.h"
#include "../logger.h"

VideoAnimation::VideoAnimation(TextureData *textureData, Video *video)
{
  this->textureData = textureData;
  this->video = video;
}

VideoAnimation::~VideoAnimation(void) {

}

void VideoAnimation::update(int delta) {
  if (previousFrame != currentFrame) {
    auto frame = video->nextFrame();
    if (frame != nullptr) {
      textureData->updateTexture(frame);
    }
  }
}
