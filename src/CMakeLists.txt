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

find_package(OpenGL REQUIRED)

find_library(corefoundation_lib CoreFoundation)

set(engine_libs
  SDL2
  ASSIMP
  GLEW
  SOIL
  ${OPENGL_LIBRARY}
  ${corefoundation_lib}
)

add_library (engine ${engine_source_files})
target_link_libraries (engine ${engine_libs})

add_executable (game main.cpp)
target_link_libraries (game engine)
