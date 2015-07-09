#
#  Author: Shervin Aflatooni
#

cmake_minimum_required (VERSION 2.6)

project (Engine)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Engine_SOURCE_DIR}/../CMakeModules)

# add_definitions( -DEMSCRIPTEN=${EMSCRIPTEN} )

file(GLOB TARGET_INC ${Engine_SOURCE_DIR}/*.h)
file(GLOB TARGET_INC_COMPONENTS ${Engine_SOURCE_DIR}/components/*.h)

file(GLOB TARGET_SRC
  ${Engine_SOURCE_DIR}/*.cpp
  ${Engine_SOURCE_DIR}/*.c
)

file(GLOB TARGET_SRC_COMPONENTS
${Engine_SOURCE_DIR}/components/*.cpp
${Engine_SOURCE_DIR}/components/*.c
)

find_package(GLM REQUIRED)

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_SRC_COMPONENTS} ${TARGET_INC} ${TARGET_INC_COMPONENTS})

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

# Dependency: FFmpeg (required)

FIND_PACKAGE( FFmpeg )
IF ( MINGW AND CMAKE_TOOLCHAIN_FILE)
	PKG_CHECK_MODULES (FFMPEG_PKG REQUIRED libavcodec libavfilter libavutil libavdevice libavformat libavformat libswscale)
	IF (FFMPEG_PKG_FOUND)
		MESSAGE( "FFmpeg cflags found through pkg-config: ${FFMPEG_PKG_CFLAGS}" )
		MESSAGE( "FFmpeg ldflags found through pkg-config: ${FFMPEG_PKG_LDFLAGS}" )
		STRING(REGEX REPLACE ";" " " FFMPEG_PKG_CFLAGS "${FFMPEG_PKG_CFLAGS}")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FFMPEG_PKG_CFLAGS}")
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FFMPEG_PKG_CFLAGS}")
		SET(FFMPEG_LIBRARIES ${FFMPEG_LIBRARY} ${FFMPEG_PKG_LDFLAGS})
		MESSAGE("FFMPEG_LIBRARIES ${FFMPEG_LIBRARIES}")
	ELSE (FFMPEG_PKG_FOUND)
		MESSAGE( FATAL_ERROR "FFmpeg cflags/ldflags not found through pkg-config." )
	ENDIF (FFMPEG_PKG_FOUND)
ENDIF()
IF(FFMPEG_LIBAVFORMAT_FOUND)
	MESSAGE(STATUS "avformat library found: ${FFMPEG_LIBAVFORMAT_LIBRARIES}")
ELSE()
	MESSAGE(STATUS "avformat library not found.")
ENDIF()
IF(FFMPEG_LIBAVCODEC_FOUND)
	MESSAGE(STATUS "avcodec library found: ${FFMPEG_LIBAVCODEC_LIBRARIES}")
ELSE()
	MESSAGE(STATUS "avcodec library not found.")
ENDIF()
IF(FFMPEG_LIBAVUTIL_FOUND)
	MESSAGE(STATUS "avutil library found: ${FFMPEG_LIBAVUTIL_LIBRARIES}")
ELSE()
	MESSAGE(STATUS "avutil library not found.")
ENDIF()
IF(FFMPEG_LIBSWSCALE_FOUND)
	MESSAGE(STATUS "swscale library found: ${FFMPEG_LIBSWSCALE_LIBRARIES}")
ELSE()
	MESSAGE(STATUS "swscale library not found.")
ENDIF()
IF(FFMPEG_FOUND)
	INCLUDE_DIRECTORIES(${FFMPEG_INCLUDE_DIR} ${FFMPEG_INCLUDE_DIRS})
	MESSAGE("Found all FFmpeg libraries in ${FFMPEG_LIBRARIES}.")
ELSE()
	MESSAGE(FATAL_ERROR "Some FFmpeg libraries are missing.")
ENDIF()

  find_library(corefoundation_lib CoreFoundation)
  set(engine_libs
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${GLEW_LIBRARIES}
    ${corefoundation_lib}
    ${FFMPEG_LIBRARIES}
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
