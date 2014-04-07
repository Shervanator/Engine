#include "GameManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv){
	GameManager gm;

	gm.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	bool quit = false;
	while (!gm.shouldQuit())
	{
		gm.tick();
	}

	gm.clean();

	return 0;
}