#ifndef SHADER_H
#define SHADER_H

#ifdef _WIN32
//#define GLEW_STATIC 1
#include <GL/glew.h>
#else
#define GL_GLEXT_PROTOTYPES
#include "SDL/SDL_opengl.h"
#endif

class Shader
{
public:
	Shader(void);
	Shader(const char* vert_src, const char* frag_src);
	~Shader(void);

	void addVertex(const char* vert_src);
	void addFragment(const char* frag_src);
	void link(void);
	GLuint getProgram(void);
private:
	GLuint	g_shVert;
	GLuint	g_shFrag;
	GLuint	g_shProg;
};

#endif