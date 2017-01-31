#
#  Author: Shervin Aflatooni
#

cmake_minimum_required(VERSION 2.8)

project (Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)

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

set ( WHEREAMI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/whereami/src/ )
set ( WHEREAMI_LIBRARY whereami )

set ( IMGUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/ )
set ( IMGUI_LIBRARY imgui )


IF (EMSCRIPTEN)
  add_definitions( -DGLES2=1 )

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/src/example/assets/ -s TOTAL_MEMORY=38000000 -s USE_SDL=2 -std=c++1y")
  add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/example/assets/")

  set(ENGINE_LIBS
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ELSEIF (ANDROID)
  add_definitions( -DGLES2=1 )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

  set(ENGINE_LIBS
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++1y")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${GLEW_LIBRARIES}
    ${WHEREAMI_LIBRARY}
    ${IMGUI_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${WHEREAMI_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ENDIF ()

include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
