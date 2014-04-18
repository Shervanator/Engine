CC = gcc
CXX = g++
CXXFLAGS = -g -O0 -std=c++11 -Wall
LDFLAGS = -I/usr/local/Cellar/glm/0.9.5.2/include -I/usr/local/Cellar/sdl2/2.0.2/include -I/usr/local/Cellar/glew/1.10.0/include -L/usr/local/Cellar/sdl2/2.0.2/lib -L/usr/local/Cellar/glew/1.10.0/lib
LDLIBS = -framework OpenGL -lSDL2 -lGLEW

OBJS = ModelInstance.o ModelAsset.o KeyboardHandler.o Camera.o GLManager.o GLEWManager.o SDLManager.o GameManager.o Shader.o main.o
SRCS = ModelInstance.cpp ModelAsset.cpp KeyboardHandler.cpp Camera.cpp GLManager.cpp GLEWManager.cpp SDLManager.cpp GameManager.cpp Shader.cpp main.cpp

all: engine

engine: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o engine $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ -MF  ./.depend;

include .depend

tags: $(SRCS)
	ctags --extra=+f $(SRCS)

clean:
	/bin/rm $(OBJS)

realclean: clean
	/bin/rm engine
