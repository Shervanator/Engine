IF (EMSCRIPTEN)
  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
  )
ELSE ()
  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
  )
ENDIF ()

include_directories(${ENGINE_INCLUDES})

add_subdirectory( engine )
add_subdirectory( example )
