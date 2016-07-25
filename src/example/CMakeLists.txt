IF (ANDROID)
  set(ANDROID_BIN_ROOT ${CMAKE_BINARY_DIR}/android-project)
  add_custom_target(android-install ${ANDROID_ANT} ${ANT_INSTALL_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
  add_custom_target(android-backtrace ${ANDROID_ADB} logcat WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
  add_custom_target(android-build ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
  add_custom_target(android-start ${ANDROID_ADB} shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity WORKING_DIRECTORY ${ANDROID_BIN_ROOT})

  add_library (game ${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/SDL/src/main/android/SDL_android_main.c main.cpp)
  target_link_libraries (game engine)

  # add_custom_command(TARGET game POST_BUILD COMMAND ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})

  add_custom_command(TARGET game PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_CURRENT_SOURCE_DIR}/android-project/
      ${ANDROID_BIN_ROOT}/)

  add_custom_command(TARGET game PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_CURRENT_SOURCE_DIR}/assets/
      ${ANDROID_BIN_ROOT}/assets)

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ ${ANDROID_BIN_ROOT}/libs/${ANDROID_NDK_ABI_NAME})
ELSE ()
  add_executable (game main.cpp)
  target_link_libraries (game engine)

  add_custom_command(TARGET game PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_CURRENT_SOURCE_DIR}/assets
      $<TARGET_FILE_DIR:game>/assets)
ENDIF ()
