execute_process( COMMAND git submodule update --init --recursive )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)

IF (EMSCRIPTEN)
ELSEIF (ANDROID)
  set( SDL_STATIC ON CACHE BOOL "Build the static SDL library" )
  set( SDL_SHARED OFF CACHE BOOL "Build the shared SDL library" )
  # set( SDL_FILESYSTEM FALSE )
  set( PTHREADS OFF CACHE BOOL "Pthread support" )
  add_definitions(-DGL_GLEXT_PROTOTYPES)
  add_subdirectory( SDL )
ELSE ()
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/)
  IF (WIN32)
    add_library (whereami STATIC ${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/whereami.c ${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/whereami.h)
  ELSE ()
    add_library (whereami SHARED ${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/whereami.c ${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/whereami.h)
  ENDIF ()
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

set( ASSIMP_BUILD_3DS_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_3DS_EXPORTER)

set( ASSIMP_BUILD_AC_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_AC_EXPORTER)

set( ASSIMP_BUILD_ASE_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_ASE_EXPORTER)

set( ASSIMP_BUILD_ASSBIN_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_ASSBIN_EXPORTER)

set( ASSIMP_BUILD_ASSXML_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_ASSXML_EXPORTER)

set( ASSIMP_BUILD_B3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_B3D_EXPORTER)

set( ASSIMP_BUILD_BVH_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_BVH_EXPORTER)

set( ASSIMP_BUILD_COLLADA_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_COLLADA_EXPORTER)

set( ASSIMP_BUILD_DXF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_DXF_EXPORTER)

set( ASSIMP_BUILD_CSM_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_CSM_EXPORTER)

set( ASSIMP_BUILD_HMP_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_HMP_EXPORTER)

set( ASSIMP_BUILD_IRRMESH_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_IRRMESH_EXPORTER)

set( ASSIMP_BUILD_IRR_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_IRR_EXPORTER)

set( ASSIMP_BUILD_LWO_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_LWO_EXPORTER)

set( ASSIMP_BUILD_LWS_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_LWS_EXPORTER)

set( ASSIMP_BUILD_MD2_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MD2_EXPORTER)

set( ASSIMP_BUILD_MD3_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MD3_EXPORTER)

set( ASSIMP_BUILD_MD5_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MD5_EXPORTER)

set( ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MDC_EXPORTER)

set( ASSIMP_BUILD_MDL_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MDL_EXPORTER)

set( ASSIMP_BUILD_NFF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_NFF_EXPORTER)

set( ASSIMP_BUILD_NDO_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_NDO_EXPORTER)

set( ASSIMP_BUILD_OFF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OFF_EXPORTER)

set( ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OBJ_EXPORTER)

set( ASSIMP_BUILD_OGRE_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OGRE_EXPORTER)

set( ASSIMP_BUILD_OPENGEX_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OPENGEX_EXPORTER)

set( ASSIMP_BUILD_PLY_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_PLY_EXPORTER)

set( ASSIMP_BUILD_MS3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MS3D_EXPORTER)

set( ASSIMP_BUILD_COB_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_COB_EXPORTER)

set( ASSIMP_BUILD_BLEND_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_BLEND_EXPORTER)

set( ASSIMP_BUILD_IFC_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_IFC_EXPORTER)

set( ASSIMP_BUILD_XGL_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_XGL_EXPORTER)

set( ASSIMP_BUILD_FBX_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_FBX_EXPORTER)

set( ASSIMP_BUILD_Q3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_Q3D_EXPORTER)

set( ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_Q3BSP_EXPORTER)

set( ASSIMP_BUILD_RAW_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_RAW_EXPORTER)

set( ASSIMP_BUILD_SIB_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_SIB_EXPORTER)

set( ASSIMP_BUILD_SMD_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_SMD_EXPORTER)

set( ASSIMP_BUILD_STL_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_STL_EXPORTER)

set( ASSIMP_BUILD_TERRAGEN_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_TERRAGEN_EXPORTER)

set( ASSIMP_BUILD_3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_3D_EXPORTER)

set( ASSIMP_BUILD_X_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_XFILE_EXPORTER)

set( ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_GLTF_EXPORTER)

set( ASSIMP_BUILD_3MF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_3MF_EXPORTER)


add_subdirectory( assimp )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
IF (WIN32)
  add_library (imgui STATIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp)
ELSE ()
  add_library (imgui SHARED ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp)
ENDIF ()
