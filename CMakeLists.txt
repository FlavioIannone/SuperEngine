cmake_minimum_required(VERSION 3.10)
project(SuperEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(FetchContent)

# SDL2 library
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.30.0 
)
FetchContent_MakeAvailable(SDL2)

# Source files
add_executable(SuperEngine
    ./src/main.cpp # main
    # Engine
    ./src/Core/Engine/Engine.cpp 
    # SceneManagement
    ./src/Core/SceneManagement/Scene.cpp
    ./src/Core/GameObject.cpp # GameObject
    ./src/Core/Time.cpp # Time
    # Components
    ./src/Core/Components/Transform.cpp
    ./src/Core/Components/Camera.cpp
    # Math
    ./src/Core/Math/Vector2.cpp
    ./src/Core/Math/Vector3.cpp
    ./src/Core/Math/Vector4.cpp
    ./src/Core/Math/Matrix4x4.cpp
)


# --- QUALITY OF LIFE: Kill the program on build ---
if(WIN32)
    add_custom_target(KillRunningEngine
        COMMAND taskkill /f /fi "imagename eq SuperEngine.exe"
        COMMENT "Killing eventual instances of the engine..."
    )

    add_dependencies(SuperEngine KillRunningEngine)
endif()


target_link_libraries(SuperEngine PRIVATE SDL2::SDL2-static)
target_include_directories(SuperEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)