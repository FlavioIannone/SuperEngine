cmake_minimum_required(VERSION 3.10...3.30)
project(SuperEngineProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(vendor)

add_subdirectory(SuperEngine)

add_subdirectory(Sandbox)

if(WIN32)
    add_custom_target(KillRunningEngine
        COMMAND taskkill /f /fi "imagename eq SuperEngine.exe"
        COMMENT "Killing eventual instances of the engine..."
    )

    add_dependencies(SuperEngine KillRunningEngine)
endif()