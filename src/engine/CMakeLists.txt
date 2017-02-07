#
#  Author: Shervin Aflatooni
#

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(BUILD_SHARED_LIBS TRUE)

file(GLOB TARGET_INC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
list(REMOVE_ITEM TARGET_INC ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h)
file(GLOB TARGET_INC_COMPONENTS ${CMAKE_CURRENT_SOURCE_DIR}/components/*.h)

file(GLOB TARGET_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

file(GLOB TARGET_SRC_COMPONENTS
  ${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/components/*.c
)

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_SRC_COMPONENTS} ${TARGET_INC} ${TARGET_INC_COMPONENTS})

IF (ANDROID)
  add_library (engine STATIC ${TARGET_SRC})
ELSE ()
  add_library (engine SHARED ${TARGET_SRC})
ENDIF ()

target_link_libraries (engine ${ENGINE_LIBS})
set_target_properties(engine PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(engine)

install (TARGETS engine DESTINATION lib)
install (FILES ${TARGET_INC} DESTINATION include/engine)
install (FILES ${TARGET_INC_COMPONENTS} DESTINATION include/engine/components)

# TODO: ADD THIS BACK WHEN NEEDED
# IF (NOT TARGET uninstall)
#   # add make uninstall capability
#   configure_file("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
#   add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
# ENDIF()
