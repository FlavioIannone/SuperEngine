cmake_minimum_required(VERSION 3.10)

project(SuperEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SuperEngine ./src/main.cpp # main
    ./src/Core/Engine/Engine.cpp # Engine
    # SceneManagement
    ./src/Core/SceneManagement/Scene.cpp
    ./src/Core/GameObject.cpp # GameObject
    ./src/Core/Time.cpp # Time
    # Components
    ./src/Core/Components/Transform.cpp
)

target_include_directories(SuperEngine PRIVATE ${CMAKE_SOURCE_DIR}/include)
