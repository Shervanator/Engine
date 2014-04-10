CC = gcc
CXX = g++
CXXFLAGS = -g -O0 -std=c++11
LDFLAGS = -I/usr/local/Cellar/sdl2/2.0.2/include -I/usr/local/Cellar/glew/1.10.0/include -L/usr/local/Cellar/sdl2/2.0.2/lib -L/usr/local/Cellar/glew/1.10.0/lib
LDLIBS = -framework OpenGL -lSDL2 -lGLEW

OBJS = GameManager.o Shader.o main.o
SRCS = GameManager.cpp Shader.cpp main.cpp

all: engine

engine: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o engine $(OBJS) $(LDLIBS)

GameManager.o: GameManager.h
Shader.o: Shader.h
main.o: GameManager.h

tags: $(SRCS)
	ctags --extra=+f $(SRCS)

clean:
	/bin/rm $(OBJS)

realclean: clean
	/bin/rm engine
