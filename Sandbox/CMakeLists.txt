file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
add_executable(Sandbox ${GAME_SOURCES})

target_link_libraries(Sandbox PRIVATE SuperEngine)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/" 
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/")