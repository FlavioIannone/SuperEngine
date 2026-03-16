#define SDL_MAIN_HANDLED
#include "Core/Engine/Engine.h"
#include "Core/Components/Transform.h"
#include "Core/Components/Test.h"

int main(int argc, char **args)
{
    using namespace SuperEngine;
    Engine engine = Engine();

    auto worldScene = engine.CreateScene("World");
    auto player = worldScene->CreateGameObject("Player");
    player->AddComponent<Transform>();

    engine.Run();
    return 0;
}