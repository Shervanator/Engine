cmake_minimum_required (VERSION 2.6)

project (Engine)

set(engine_source_files
  VisibleObject.cpp
  Game.cpp
  Camera.cpp
  GLEWManager.cpp
  GLManager.cpp
  GameManager.cpp
  KeyboardHandler.cpp
  Mesh.cpp
  SDLManager.cpp
  SceneNode.cpp
  Shader.cpp
  Texture.cpp
  main.cpp
)

set(engine_header_files
  VisibleObject.h
  Game.h
  Camera.h
  GLEWManager.h
  GLManager.h
  GameManager.h
  GameObject.h
  KeyboardHandler.h
  Mesh.h
  SDLManager.h
  SceneNode.h
  Shader.h
  Texture.h
  Vertex.h
)

FIND_LIBRARY(opengl_lib OpenGL)
FIND_LIBRARY(corefoundation_lib CoreFoundation)

set(engine_libs
  SDL2
  ASSIMP
  GLEW
  SOIL
  ${opengl_lib}
  ${corefoundation_lib}
)

add_executable (engine ${engine_source_files} ${engine_header_files})
target_link_libraries (engine ${engine_libs})
