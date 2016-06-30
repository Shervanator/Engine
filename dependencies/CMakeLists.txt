execute_process( COMMAND git submodule init )
execute_process( COMMAND git submodule update )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)


add_subdirectory( SDL )

add_subdirectory( glew )

set( ASSIMP_BUILD_ASSIMP_TOOLS OFF )
set( ASSIMP_BUILD_SAMPLES      OFF )
set( ASSIMP_BUILD_TESTS        OFF )

add_subdirectory( assimp )
