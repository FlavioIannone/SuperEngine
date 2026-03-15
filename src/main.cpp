#include "Core/Engine/Engine.h"
#include "Core/Components/Transform.h"
#include "Core/Components/Test.h"

int main()
{
    using namespace SuperEngine;
    Engine engine = Engine();

    auto worldScene = engine.CreateScene("World");
    auto player = worldScene->CreateGameObject("Player");
    player->AddComponent<Transform>();
    player->AddComponent<Test>();

    engine.Run();
    return 0;
}