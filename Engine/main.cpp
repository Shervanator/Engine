#include "GameManager.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

int main(int argc, char **argv){
  GameManager gm(SCREEN_WIDTH, SCREEN_HEIGHT);

  while (!gm.shouldQuit())
  {
    gm.tick();
  }

  return 0;
}
