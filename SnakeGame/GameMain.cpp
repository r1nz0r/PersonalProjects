#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Exception.h"
#include "Game.h"

int main()
{
    Game* game = new Game();
    game->Start();
    
    while (game->IsWindowOpen())
    {
        game->Update();
        game->Render();
    }

    delete game;
    game = nullptr;

    return 0;
}
