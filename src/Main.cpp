#include <iostream>
#include "Game.h"
#include"Constants.h"
#undef main

int main()
{
    MarkTwo::GameCore::Game* game = new MarkTwo::GameCore::Game();
    game->Initialize(MarkTwo::WINDOW_WIDTH, MarkTwo::WINDOW_HEIGHT);

    while (game->IsRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();

    return 0;
}
