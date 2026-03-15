#include "Core/Engine/Engine.h"
#include <iostream>

int main()
{
    SuperEngine::Engine engine = SuperEngine::Engine();

    auto worldScene = engine.CreateScene("World");
    auto player = worldScene->CreateGameObject("Player");

    engine.Run();
    return 0;
}