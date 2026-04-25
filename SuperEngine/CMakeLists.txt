# SuperEngine/CMakeLists.txt

add_library(SuperEngine STATIC
    # Engine
    ./src/SuperEngine/Engine/Engine.cpp 
    ./src/SuperEngine/Engine/RenderingManager.cpp
    ./src/SuperEngine/Engine/AssetManager.cpp
    # Graphics
    ./src/SuperEngine/Graphics/ComputeShader.cpp 
    ./src/SuperEngine/Graphics/GraphicsDevice.cpp 
    ./src/SuperEngine/Graphics/BuiltInShaders.cpp
    ./src/SuperEngine/Graphics/Mesh/Mesh.cpp
    # SceneManagement
    ./src/SuperEngine/SceneManagement/Scene.cpp
    ./src/SuperEngine/GameObject.cpp 
    ./src/SuperEngine/Time.cpp 
    # Components
    ./src/SuperEngine/Components/Transform.cpp
    ./src/SuperEngine/Components/Camera.cpp
    ./src/SuperEngine/Components/MeshRenderer.cpp
    # Math
    ./src/SuperEngine/Math/Vector2.cpp
    ./src/SuperEngine/Math/Vector3.cpp
    ./src/SuperEngine/Math/Vector4.cpp
    ./src/SuperEngine/Math/Matrix4x4.cpp
)

target_include_directories(SuperEngine PUBLIC "include")

target_link_libraries(SuperEngine 
    PUBLIC SDL2::SDL2-static 
    PRIVATE d3d11 dxgi d3dcompiler
)

add_custom_target(CopyEngineAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    COMMENT "Syncing engine's assets..."
)

add_dependencies(SuperEngine CopyEngineAssets)