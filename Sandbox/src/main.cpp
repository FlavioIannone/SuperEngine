#define SDL_MAIN_HANDLED
#include "TestScript.cpp"
#include "CubeScript.cpp"
#include "SuperEngine/SuperEngine.h"
#include <vector>

int main(int argc, char **args)
{
    using namespace SuperEngine;

    if (!Engine::GetInstance().Init(1280, 720, false))
    {
        std::cout << "Error initializing the engine\n";
        return 1;
    }
    auto worldScene = Engine::GetInstance().CreateScene("World");

    auto worldSceneCamera = worldScene->CreateCamera("Main Camera", Vector3(0, 0, -5));
    worldSceneCamera->AddComponent<Camera>(70.0f, 0.1f, 100.0f);

    std::vector<GameObject *> cubesPool;

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 3000; i++)
    {

        float rX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float rY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float rZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        float posX = (rX * 40.0f) - 20.0f;
        float posY = (rY * 40.0f) - 20.0f;
        float posZ = (rZ * 40.0f) + 10.0f;

        auto cube = worldScene->CreateCube(Vector3(posX, posY, posZ));

        cube->AddComponent<TestScript>();

        cubesPool.push_back(cube);
    }

    Engine::GetInstance().Run();
    return 0;
}