cmake_minimum_required (VERSION 2.6)

project (Engine)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Engine_SOURCE_DIR}/../CMakeModules)

# add_definitions( -DEMSCRIPTEN=${EMSCRIPTEN} )

set(engine_source_files
  GameObject.cpp
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
  Engine.h
  GLManager.h
  Shader.h
  SceneNode.h
  Transform.h
  SDLManager.h
  GLEWManager.h
  Game.h
  KeyboardHandler.h
  VisibleObject.h
  GameObject.h
  Mesh.h
  Vertex.h
  Texture.h
  Camera.h
)

find_package(GLM REQUIRED)

IF (EMSCRIPTEN)
  SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -g -Wall -s FULL_ES2=1 --preload-file ../assets/ -s ASSERTIONS=2")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -s FULL_ES2=1 --preload-file ../assets/ -s ASSERTIONS=2")

  find_package(SOIL)

  include_directories(${GLM_INCLUDE_DIRS} ${SOIL_INCLUDE_DIRS} /Users/shervinaflatooni/Git/assimp/include/)

  ADD_EXECUTABLE(engine.html main.cpp ${engine_source_files})

  target_link_libraries (engine.html /Users/shervinaflatooni/Git/assimp/build.em/code/libassimp.dylib)
ELSE ()
  find_package(OpenGL REQUIRED)
  find_package(SDL2 REQUIRED)
  find_package(ASSIMP REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(SOIL REQUIRED)

  find_library(corefoundation_lib CoreFoundation)

  set(engine_libs
    ${SOIL_LIBRARIES}
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${GLEW_LIBRARIES}
    ${corefoundation_lib}
  )

  include_directories(${SDL2_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SOIL_INCLUDE_DIRS})

  add_library (engine SHARED ${engine_source_files})
  target_link_libraries (engine ${engine_libs})

  add_executable (game main.cpp)
  target_link_libraries (game engine)

  install (TARGETS engine DESTINATION lib)
  install (FILES ${engine_header_files} DESTINATION include/engine)
ENDIF ()
