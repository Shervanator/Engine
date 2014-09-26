cmake_minimum_required (VERSION 2.6)

project (Engine)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Engine_SOURCE_DIR}/../CMakeModules)

# add_definitions( -DEMSCRIPTEN=${EMSCRIPTEN} )

file(GLOB_RECURSE TARGET_INC ${Engine_SOURCE_DIR}/*.h)

file(GLOB_RECURSE TARGET_SRC
  ${Engine_SOURCE_DIR}/*.cpp
  ${Engine_SOURCE_DIR}/*.c
)

find_package(GLM REQUIRED)

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_INC})

IF (EMSCRIPTEN)
  add_definitions( -DGLES2=1 )

  SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -g -Wall --preload-file ../assets/ -s ASSERTIONS=2 -s TOTAL_MEMORY=39554432")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ../assets/ -s ASSERTIONS=2 -s TOTAL_MEMORY=39554432")

  include_directories(${GLM_INCLUDE_DIRS} /Users/shervinaflatooni/Git/assimp/include/)

  add_library (engine SHARED ${TARGET_SRC})
  target_link_libraries (engine /Users/shervinaflatooni/Git/assimp/build.em/code/libassimp.so)

  add_executable (game.html main.cpp)
  target_link_libraries (game.html engine)
ELSE ()
  SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -g -Wall")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -stdlib=libc++")
  find_package(OpenGL REQUIRED)
  find_package(SDL2 REQUIRED)
  find_package(ASSIMP REQUIRED)
  find_package(GLEW REQUIRED)

  find_library(corefoundation_lib CoreFoundation)

  set(engine_libs
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${GLEW_LIBRARIES}
    ${corefoundation_lib}
  )

  include_directories(${SDL2_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

  add_library (engine SHARED ${TARGET_SRC})
  target_link_libraries (engine ${engine_libs})

  add_executable (game main.cpp)
  target_link_libraries (game engine)

  install (TARGETS engine DESTINATION lib)
  install (FILES ${TARGET_INC} DESTINATION include/engine)
ENDIF ()
