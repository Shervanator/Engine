#
#  Author: Shervin Aflatooni
#

cmake_minimum_required (VERSION 2.6)

project (Engine)

#############

add_subdirectory( ${PROJECT_SOURCE_DIR}/dependencies/SDL )

set ( SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/SDL/include )
set ( SDL2_LIBRARY SDL2 )

#############

add_subdirectory( ${PROJECT_SOURCE_DIR}/dependencies/glew )

set ( GLEW_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/dependencies/glew/include )
set ( GLEW_LIBRARIES libglew_shared )

#############

set( ASSIMP_BUILD_ASSIMP_TOOLS OFF )
set( ASSIMP_BUILD_SAMPLES      OFF )
set( ASSIMP_BUILD_TESTS        OFF )

add_subdirectory( ${PROJECT_SOURCE_DIR}/dependencies/assimp )

set ( ASSIMP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dependencies/assimp/include )
set ( ASSIMP_LIBRARY assimp )

#############

set ( GLM_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/dependencies/glm/ )

#############
add_subdirectory( ${PROJECT_SOURCE_DIR}/src )
