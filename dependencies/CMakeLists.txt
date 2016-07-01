execute_process( COMMAND git submodule init )
execute_process( COMMAND git submodule update )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)


add_subdirectory( SDL )

add_subdirectory( glew )

set( ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build assimp tools" )
set( ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build assimp tests" )
set( ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Build assimp samples" )

add_subdirectory( assimp )
