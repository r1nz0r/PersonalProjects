#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Exception.h"
#include "Game.h"

int main()
{
    Game* game = new Game();

    game->Start();
    game->Update();

    delete game;
    game = nullptr;

    return 0;
}
