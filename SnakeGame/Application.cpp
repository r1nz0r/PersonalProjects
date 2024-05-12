#include "Application.h"
#include "Game.h"
#include "Menu.h"
#include "GameSettings.h"
#include "iostream"
#include "UIManager.h"
#include "TextInputBox.h"

Application& Application::GetInstance()
{
    static Application sApplication;
    return sApplication;
}

Application::~Application()
{
    Clear();
}

void Application::ShowSettingsCheckBoxes(sf::RenderWindow& window)
{   
    _soundCheck->Draw(window);
    _musicCheck->Draw(window);
}

void Application::CreateSettingsCheckBoxes()
{
    _soundCheck = new TextInputBox(UIManager::GetInstance().GetFont(), 1u);
    _musicCheck = new TextInputBox(UIManager::GetInstance().GetFont(), 1u);    
}

void Application::ToggleCheckbox(TextInputBox* checkBox)
{
    if (!checkBox)
        return;

    if (checkBox->GetText() == "")
        checkBox->UpdateText("V", sf::Color::Green);
    else
        checkBox->UpdateText("", sf::Color::Black);
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
    CreateSettingsCheckBoxes();

    Game* game = new Game();

    sf::RenderWindow menuWindow { sf::VideoMode(300,500), "Menu" };

    _soundCheck->SetPosition({ menuWindow.getSize().x / 1.2f, menuWindow.getSize().y / 2.3f });
    _musicCheck->SetPosition({ menuWindow.getSize().x / 1.2f, menuWindow.getSize().y / 1.9f });

    Menu* currentMenu = nullptr;

    Menu::ItemsList settingsMenuItems
    {
        {"Sound", [this]() { std::cout << "Sound selected!" << std::endl; ToggleCheckbox(_soundCheck); }},
        {"Music", [this]() { std::cout << "Music selected!" << std::endl; ToggleCheckbox(_musicCheck); }},
    };
    Menu settingsMenu { settingsMenuItems, UIManager::GetInstance().GetFont() , menuWindow, "Settings", 20.0f};
    settingsMenu.SetMenuItemsAlignment(TextBlock::Alignment::End, TextBlock::Alignment::Center, Text::Alignment::Start);

    Menu::ItemsList difficultyItems
    {
        {"Beginner", [&game]() { std::cout << "Beginner selected!" << std::endl; game->SetDifficulty(EGameDifficulty::Beginner); }},
        {"Easy", [&game]() { std::cout << "Easy selected!" << std::endl; game->SetDifficulty(EGameDifficulty::Easy); }},
        {"Normal", [&game]() { std::cout << "Normal selected!" << std::endl; game->SetDifficulty(EGameDifficulty::Normal); }},
        {"Hard", [&game]() { std::cout << "Hard selected!" << std::endl; game->SetDifficulty(EGameDifficulty::Hard); }},
        {"Insane", [&game]() { std::cout << "Insane selected!" << std::endl; game->SetDifficulty(EGameDifficulty::Insane); }},
    };
    Menu difficultyMenu { difficultyItems, UIManager::GetInstance().GetFont(), menuWindow, "Difficulty" };

    Menu::ItemsList mainMenuItems
    {
        {"Start", [&menuWindow, &game]() { std::cout << "Start game selected!" << std::endl; menuWindow.close(); game->Start(); }},
        {"Difficulty", [&currentMenu, &difficultyMenu]() { std::cout << "Difficulty selected!" << std::endl; currentMenu = &difficultyMenu; }},
        {"Records table", []() { std::cout << "Records table!" << std::endl; }},
        {"Settings", [&currentMenu, &settingsMenu,&menuWindow, this]() { std::cout << "Settings selected!" << std::endl; currentMenu = &settingsMenu;}},
        {"Exit", [&menuWindow]() { menuWindow.close(); }}
    };
    Menu mainMenu { mainMenuItems, UIManager::GetInstance().GetFont(), menuWindow, "Snake Game" };

    settingsMenu.SetRootItem(&mainMenu);
    difficultyMenu.SetRootItem(&mainMenu);

    currentMenu = &mainMenu;

    while (menuWindow.isOpen())
    {
        sf::Event event;
        while (menuWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                menuWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.scancode == sf::Keyboard::Scancode::Escape)
                {
                    if (currentMenu->GetRootItem())
                        currentMenu = currentMenu->GetRootItem();
                }
                else
                    currentMenu->HandleInput(event);
                break;
            default:
                break;
            }
        }

        menuWindow.clear();

        if (currentMenu == &settingsMenu)
            ShowSettingsCheckBoxes(menuWindow);

        currentMenu->Draw(menuWindow);
        menuWindow.display();
    }

    while (game->IsWindowOpen())
    {
        game->Update();
        game->Render();
    }
}

