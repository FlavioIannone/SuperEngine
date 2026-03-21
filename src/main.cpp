#define SDL_MAIN_HANDLED
#include "TestScript.cpp"
#include "Core/Core.h"

int main(int argc, char **args)
{
    using namespace SuperEngine;
    Engine::GetInstance().SetWidth(1280);
    Engine::GetInstance().SetHeight(720);
    auto worldScene = Engine::GetInstance().CreateScene("World");
    auto worldSceneCamera = worldScene->CreateGameObject("Main Camera");

    worldSceneCamera->AddComponent<Camera>(70.0f, 0.1f, 1000.0f);

    auto cube = worldScene->CreateGameObject("Cube");
    cube->AddComponent<MeshRenderer>(CubeMesh());
    cube->GetTransform()->position.z = 5.0f;
    cube->AddComponent<TestScript>();

    Engine::GetInstance().Run();
    return 0;
}