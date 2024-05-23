#include "Application.h"
#include "Game.h"
#include "GameSettings.h"
#include "iostream"
#include "UIManager.h"

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
}

void Application::Run()
{       
    UIManager& uiManager = UIManager::GetInstance();    
    _game = new Game();    

    uiManager.ShowMainMenu();

    while (uiManager.IsMenuOpen() || _game->IsWindowOpen())
    {      
        if (uiManager.IsMenuOpen())
        {
            uiManager.Update();
        }
        else
        {
            _game->Update();
            _game->Render();
        }
    }
}

