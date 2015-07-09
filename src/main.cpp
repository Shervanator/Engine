//
//  Author: Shervin Aflatooni
//

#include "Engine.h"

#include "components/MeshRenderer.h"
#include "components/Camera.h"
#include "components/FreeMove.h"
#include "components/FreeLook.h"
#include "components/DirectionalLight.h"
#include "components/SpotLight.h"
#include "components/PointLight.h"
#include "components/Sphere.h"

#include "Plane.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "MeshLoader.h"
#include "MediaLoader.h"
#include "Video.h"

#include <stdio.h>

class CoolGame : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(int delta);

private:
  Camera *primary_camera;
  // TextureData *textureData;
  // AVFormatContext *pFormatCtx = NULL;
  // int i, videoStream;
  // AVCodecContext *pCodecCtx;
  // AVCodec *pCodec;
  // AVFrame *pFrame;
  // AVFrame *pFrameRGB;
  // int numBytes;
  // uint8_t *buffer;
  // struct SwsContext * pSwsCtx;
  // AVPacket packet;
  // int frameFinished;
  // int accumulator = 0;
  // int frameRate;
};

void CoolGame::update(int delta)
{
  // accumulator += delta;
  //
  // if (accumulator >= (1000.0 / frameRate)) {
  //   while (av_read_frame(pFormatCtx, &packet) >= 0) {
  //
  //
  //     if (packet.stream_index == videoStream) {
  //       avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
  //
  //       if (frameFinished) {
  //         sws_scale(pSwsCtx,
  //                   (const uint8_t * const *) pFrame->data,
  //                   pFrame->linesize, 0, pCodecCtx->height,
  //                   pFrameRGB->data,
  //                   pFrameRGB->linesize);
  //
  //         log_info("READING FRAME");
  //
  //         frameFinished = 0;
  //         break;
  //       }
  //
  //     }
  //   }
  //
  //   log_info("UPDATE TEXTURE %p", pFrameRGB->data[0]);
  //   textureData->updateTexture(pFrameRGB->data[0]);
  //
  //   av_free_packet(&packet);
  //
  //   accumulator = 0;
  // }


  Game::update(delta);
}

// CoolGame::~CoolGame() {
//  // Free the RGB image
//  av_free(buffer);
//  av_free(pFrameRGB);
//
//  // Free the YUV frame
//  av_free(pFrame);
//
//  // Close the codec
//  avcodec_close(pCodecCtx);
//
//  // Close the video file
//  avformat_close_input(&pFormatCtx);
// }

void CoolGame::init(GLManager *glManager)
{
  // textureData = new TextureData(pCodecCtx->width, pCodecCtx->height, pFrameRGB->data[0], GL_RGBA, GL_TEXTURE_2D, GL_LINEAR);
  // Texture* texture = new Texture(textureData);

  // MediaLoader il = MediaLoader(texture);
  // il.getEntity()->getTransform().scale(glm::vec3(10, 10, 10));
  // il.getEntity()->getTransform().rotate(glm::vec3(1, 0, 0), 90 * 0.0174532925);
  // addToScene(il.getEntity());

  Video *vid = new Video("/Users/shervinaflatooni/Downloads/Mograph_test_project/\(Footage\)/user\ replaceable\ assets/videos/movie\ 01.mov");

  MediaLoader il = MediaLoader(vid);
  il.getEntity()->getTransform().scale(glm::vec3(10, 10, 10));
  il.getEntity()->getTransform().rotate(glm::vec3(1, 0, 0), 90 * 0.0174532925);
  addToScene(il.getEntity());

  Entity *ent = new Entity();
  Camera *cam2 = new Camera(45.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.1f, 100.0f);
  ent->addComponent(cam2);
  ent->getTransform().setPosition(glm::vec3(0, 0, 10));
  ent->addComponent(new FreeMove());
  ent->addComponent(new FreeLook());
  addToScene(ent);

  primary_camera = cam2;

  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
