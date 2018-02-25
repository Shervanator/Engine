#
#  Author: Shervin Aflatooni
#

cmake_minimum_required(VERSION 2.8)

project (Engine)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cotire/CMake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
include(cotire)
include(${CP_CMAKE_DIR}/macros.cmake)

IF (ANDROID)
  include(${CP_CMAKE_DIR}/android.cmake)
ENDIF ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(dependencies)

set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL/include )
set ( SDL2_LIBRARY SDL2 )

set ( GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew/include )
set ( GLEW_LIBRARIES libglew_shared )

set ( ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include )
set ( ASSIMP_LIBRARY assimp )

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/ )

set ( STB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb/ )

set ( WHEREAMI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/whereami/src/ )
set ( WHEREAMI_LIBRARY whereami )

set ( IMGUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/ )
set ( IMGUI_LIBRARY imgui )

set ( BULLET_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/bullet3/src/ )
set ( BULLET_LIBRARY BulletDynamics BulletCollision LinearMath )

IF (EMSCRIPTEN)
  SET ( CMAKE_SHARED_LINKER_FLAGS "-Oz --closure 1" )
  SET ( CMAKE_STATIC_LINKER_FLAGS "-Oz --closure 1" )
  SET ( CMAKE_EXE_LINKER_FLAGS "-Oz --closure 1")

  SET(CMAKE_CXX_FLAGS "--closure 1 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/src/example/assets/ -s TOTAL_MEMORY=536870912 -s USE_SDL=2 -std=c++14 -Oz")
  add_definitions( -DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/example/assets/" )

  set(ENGINE_LIBS
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
    ${BULLET_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${STB_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${IMGUI_INCLUDE_DIRS}
    ${BULLET_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
  ELSEIF (ANDROID)
  add_definitions( -DGLES2=1 )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

  set(ENGINE_LIBS
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
    ${BULLET_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${STB_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${IMGUI_INCLUDE_DIRS}
    ${BULLET_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++14")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${GLEW_LIBRARIES}
    ${WHEREAMI_LIBRARY}
    ${IMGUI_LIBRARY}
    ${BULLET_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${STB_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${GLEW_INCLUDE_DIRS}
    ${WHEREAMI_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    ${BULLET_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ENDIF ()

include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
