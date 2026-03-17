#define SDL_MAIN_HANDLED
#include "Core/Engine/Engine.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Test.h"

int main(int argc, char **args)
{
    using namespace SuperEngine;
    auto worldScene = Engine::GetInstance().CreateScene("World");
    auto worldSceneCamera = worldScene->CreateGameObject("Main Camera");

    worldSceneCamera->AddComponent<Camera>();

    auto player = worldScene->CreateGameObject("Player");

    Engine::GetInstance().Run();
    return 0;
}