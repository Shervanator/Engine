cmake_minimum_required (VERSION 2.6)

project (Engine)

set(engine_source_files
  Transform.cpp
  VisibleObject.cpp
  Game.cpp
  Camera.cpp
  GLEWManager.cpp
  GLManager.cpp
  Engine.cpp
  KeyboardHandler.cpp
  Mesh.cpp
  SDLManager.cpp
  SceneNode.cpp
  Shader.cpp
  Texture.cpp
)

set(engine_header_files
  Transform.h
  VisibleObject.h
  Game.h
  Camera.h
  GLEWManager.h
  GLManager.h
  Engine.h
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

add_library (engine ${engine_source_files} ${engine_header_files})
target_link_libraries (engine ${engine_libs})

add_executable (game main.cpp)
target_link_libraries (game engine)
