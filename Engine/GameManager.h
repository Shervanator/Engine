#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SDL.h>
#include <string>

#ifdef _WIN32
//#define GLEW_STATIC 1
#include <GL/glew.h>
#else
#define GL_GLEXT_PROTOTYPES
#include "SDL/SDL_opengl.h"
#endif

#include "Shader.h"

class GameManager
{
public:
	GameManager(void);
	~GameManager(void);

	int init(const int width, const int height);
	void tick(void);
	void clean(void);
	bool shouldQuit(void);
private:
	int initSDL(const int width, const int height, Uint32 flags);
	void initGL(void);
	void logSDLError(const std::string &msg);
	void render(void);
	void createShaders(void);
	void createVAO(void);

	SDL_Event event;
	SDL_Window *win;
	SDL_GLContext glContext;

	Shader *shader1;
	Shader *shader2;

	GLuint	g_vao;
	GLuint	g_vbo;

	int WIDTH;
	int HEIGHT;

	bool quit;
};

#endif