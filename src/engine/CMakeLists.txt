#
#  Author: Shervin Aflatooni
#

file(GLOB TARGET_INC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB TARGET_INC_COMPONENTS ${CMAKE_CURRENT_SOURCE_DIR}/components/*.h)

file(GLOB TARGET_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

list(REMOVE_ITEM TARGET_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

file(GLOB TARGET_SRC_COMPONENTS
${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/components/*.c
)

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_SRC_COMPONENTS} ${TARGET_INC} ${TARGET_INC_COMPONENTS})

IF (EMSCRIPTEN)
  add_definitions( -DGLES2=1 )

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ../assets/ -s TOTAL_MEMORY=38000000 -s USE_SDL=2")

  set(ENGINE_LIBS
    ${ASSIMP_LIBRARY}
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
ENDIF ()

add_library (engine SHARED ${TARGET_SRC})
target_link_libraries (engine ${ENGINE_LIBS})


# install (TARGETS engine DESTINATION lib)
# install (FILES ${TARGET_INC} DESTINATION include/engine)
# install (FILES ${TARGET_INC_COMPONENTS} DESTINATION include/engine/components)

# TODO: ADD THIS BACK WHEN NEEDED
# IF (NOT TARGET uninstall)
#   # add make uninstall capability
#   configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../CMakeModules/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
#   add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
# ENDIF()
