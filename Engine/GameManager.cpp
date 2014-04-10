#include <iostream>
#include "GameManager.h"

GameManager::GameManager(void)
{
	quit = false;
}

GameManager::~GameManager(void)
{
}

int GameManager::init(const int width, const int height)
{
	// init sdl
	if (initSDL(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL) != 0)
		return 1;

	// init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	// init opengl
	initGL();

	return 0;
}

void GameManager::tick(void)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			quit = true;
		if (event.type == SDL_MOUSEBUTTONDOWN)
			glUseProgram(shader2->getProgram());
	}

	render();

	SDL_GL_SwapWindow(win);
}

bool GameManager::shouldQuit(void)
{
	return quit;
}

void GameManager::clean(void)
{
	delete shader1;
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

int GameManager::initSDL(const int width, const int height, Uint32 flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError("SDL_Init");
		return 1;
	}
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	WIDTH = width;
	HEIGHT = height;

	win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	if (win == nullptr)
	{
		logSDLError("SDL_CreateWindow");
		return 1;
	}

	glContext = SDL_GL_CreateContext(win);

	return 0;
}

void GameManager::logSDLError(const std::string &msg)
{
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

void GameManager::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void GameManager::initGL()
{
	createShaders();
	createVAO();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glViewport(0, 0, WIDTH, HEIGHT);
}

void GameManager::createShaders()
{
	const char* vert_src =
		"#version 150\n"
		"in vec2 in_Position;\n"
		"\n"
		"void main(){\n"
		"	gl_Position = vec4(in_Position, .0, 1.0);\n"
		"}";
	const char* frag_src =
		"#version 150\n"
		"out vec4 frag_Color;\n"
		"\n"
		"void main(){\n"
		"	frag_Color = vec4(1.0, .0, .0, 1.0);\n"
		"}";
	const char* frag_src2 =
		"#version 150\n"
		"out vec4 frag_Color;\n"
		"\n"
		"void main(){\n"
		"	frag_Color = vec4(.0, 1.0, .0, 1.0);\n"
		"}";

	shader1 = new Shader(vert_src, frag_src);
	shader2 = new Shader(vert_src, frag_src2);
	glUseProgram(shader1->getProgram());
}

void GameManager::createVAO()
{
	// Create our static triangle strip of 2 triangles = 4 vertices
	const float quad[8] = {
		-.5f, .5f,
		-.5f, -.5f,
		.5f, .5f,
		.5f, -.5f
	};

	// Generate ID for VAO, and bind it as the active VAO
	glGenVertexArrays(1, &g_vao);
	glBindVertexArray(g_vao);

	// Generate a VBO to store our vertex list
	glGenBuffers(1, &g_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, quad, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
