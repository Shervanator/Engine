add_executable (game main.cpp)
target_link_libraries (game engine)

add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:game>/assets)