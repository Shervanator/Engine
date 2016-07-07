execute_process( COMMAND git submodule init )
execute_process( COMMAND git submodule update )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)

IF (EMSCRIPTEN)
ELSE ()
	set( SDL_STATIC OFF CACHE BOOL "Build the static SDL library" )
	set( SDL_SHARED ON CACHE BOOL "Build the shared SDL library" )
  add_subdirectory( SDL )

  set( glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library" )
  set( glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library" )
  set( glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL "Build the single context glew library" )
  set( glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Build the multi context glew library" )

  add_subdirectory( glew )
ENDIF ()

set( ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build assimp tools" )
set( ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build assimp tests" )
set( ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Build assimp samples" )

add_subdirectory( assimp )
