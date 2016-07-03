#
#  Author: Shervin Aflatooni
#

cmake_minimum_required(VERSION 2.8.11)

project (Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

IF (EMSCRIPTEN)
  set ( BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin-emscripten )
ELSE ()
  set ( BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin )
ENDIF ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(EXECUTABLE_OUTPUT_PATH         ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}/lib)
set(CMAKE_BINARY_DIR ${BIN_DIR}/)

add_subdirectory(dependencies)

set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL/include )
set ( SDL2_LIBRARY SDL2 )

set ( GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew/include )
set ( GLEW_LIBRARIES libglew_shared )

set ( ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include )
set ( ASSIMP_LIBRARY assimp )

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/ )


IF (EMSCRIPTEN)
  add_definitions( -DGLES2=1 )

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ../../../assets/ -s TOTAL_MEMORY=38000000 -s USE_SDL=2")

  set(ENGINE_LIBS
    ${ASSIMP_LIBRARY}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -stdlib=libc++")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${GLEW_LIBRARIES}
  )

  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
  )
ENDIF ()

include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
