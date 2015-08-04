#
#  Author: Shervin Aflatooni
#

cmake_minimum_required (VERSION 2.6)

project (Engine)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Engine_SOURCE_DIR}/../CMakeModules)

file(GLOB TARGET_INC ${Engine_SOURCE_DIR}/*.h)
file(GLOB TARGET_INC_COMPONENTS ${Engine_SOURCE_DIR}/components/*.h)

file(GLOB TARGET_SRC
  ${Engine_SOURCE_DIR}/*.cpp
  ${Engine_SOURCE_DIR}/*.c
)

list(REMOVE_ITEM TARGET_SRC ${Engine_SOURCE_DIR}/main.cpp)

file(GLOB TARGET_SRC_COMPONENTS
${Engine_SOURCE_DIR}/components/*.cpp
${Engine_SOURCE_DIR}/components/*.c
)

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_SRC_COMPONENTS} ${TARGET_INC} ${TARGET_INC_COMPONENTS})

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
find_package(GLM REQUIRED)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

IF (EMSCRIPTEN)
  add_definitions( -DGLES2=1 )

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ../assets/ -s TOTAL_MEMORY=38000000")

  include_directories(${GLM_INCLUDE_DIRS} $ENV{HOME}/workspace/assimp/include/)

  add_library (engine SHARED ${TARGET_SRC})
  target_link_libraries (engine $ENV{HOME}/workspace/assimp/build.em/code/libassimp.so)

  add_executable (game main.cpp)
  target_link_libraries (game engine)
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
  install (FILES ${TARGET_INC_COMPONENTS} DESTINATION include/engine/components)
ENDIF ()
