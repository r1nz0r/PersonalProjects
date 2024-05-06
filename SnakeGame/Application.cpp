#include "Application.h"
#include "Game.h"
#include "Menu.h"

Application& Application::GetInstance()
{
    static Application sApplication;
    return sApplication;
}

Application::~Application()
{
    Clear();
}

void Application::Clear()
{
    delete _game;
    _game = nullptr;
    delete _menu;
    _menu = nullptr;
}

void Application::Run()
{
    Game* game = new Game();
    game->Start();

    while (game->IsWindowOpen())
    {
        game->Update();
        game->Render();
    }
}