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

void Application::CreateMenuItems(sf::RenderWindow& window)
{
    Menu::ItemsList settingsMenuItems
    {
        {"Sound", [this]() { std::cout << "Sound selected!" << std::endl; ToggleCheckbox(_soundCheck); }},
        {"Music", [this]() { std::cout << "Music selected!" << std::endl; ToggleCheckbox(_musicCheck); }},
    };
    _settingsMenu = new Menu { settingsMenuItems, UIManager::GetInstance().GetFont() , window, "Settings", 20.0f };
    _settingsMenu->SetMenuItemsAlignment(TextBlock::Alignment::End, TextBlock::Alignment::Center, Text::Alignment::Start);

    Menu::ItemsList difficultyItems
    {
        {"Beginner", [this]() { std::cout << "Beginner selected!" << std::endl; _game->SetDifficulty(EGameDifficulty::Beginner); _selectedMenu = _mainMenu; }},
        {"Easy", [this]() { std::cout << "Easy selected!" << std::endl; _game->SetDifficulty(EGameDifficulty::Easy); _selectedMenu = _mainMenu; }},
        {"Normal", [this]() { std::cout << "Normal selected!" << std::endl; _game->SetDifficulty(EGameDifficulty::Normal); _selectedMenu = _mainMenu; }},
        {"Hard", [this]() { std::cout << "Hard selected!" << std::endl; _game->SetDifficulty(EGameDifficulty::Hard); _selectedMenu = _mainMenu; }},
        {"Insane", [this]() { std::cout << "Insane selected!" << std::endl; _game->SetDifficulty(EGameDifficulty::Insane); _selectedMenu = _mainMenu; }},
    };
    _difficultyMenu = new Menu{ difficultyItems, UIManager::GetInstance().GetFont(), window, "Difficulty" };

    Menu::ItemsList mainMenuItems
    {
        {"Start", [this, &window]() { std::cout << "Start game selected!" << std::endl; SetMenuOpen(false); _game->Start(); }},
        {"Difficulty", [this]() { std::cout << "Difficulty selected!" << std::endl; _selectedMenu = _difficultyMenu; }},
        {"Records table", []() { std::cout << "Records table!" << std::endl; }},
        {"Settings", [this]() { std::cout << "Settings selected!" << std::endl; _selectedMenu = _settingsMenu; }},
        {"Exit", [&window]() { window.close(); }}
    };
    _mainMenu = new Menu { mainMenuItems, UIManager::GetInstance().GetFont(), window, "Snake Game" };

    _settingsMenu->SetRootItem(_mainMenu);
    _difficultyMenu->SetRootItem(_mainMenu);
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
    delete _mainMenu;
    delete _settingsMenu;
    delete _difficultyMenu;
    delete _menuWindow;
}

void Application::SetMenuOpen(bool flag)
{
    _bIsMenuOpen = flag;
    _menuWindow->setVisible(flag);
    _menuWindow->setActive(flag);
}

void Application::Run()
{
    _menuWindow = new sf::RenderWindow { sf::VideoMode(300,500), "Menu" };
    CreateMenuItems(*_menuWindow);
    CreateSettingsCheckBoxes();
    _game = new Game();

    _soundCheck->SetPosition({ _menuWindow->getSize().x / 1.2f, _menuWindow->getSize().y / 2.3f });
    _musicCheck->SetPosition({ _menuWindow->getSize().x / 1.2f, _menuWindow->getSize().y / 1.9f });

    _selectedMenu = _mainMenu;
    _bIsMenuOpen = true;

    while (_menuWindow->isOpen() && _game->IsWindowOpen())
    {      
        if (_bIsMenuOpen)
        {
            sf::Event menuEvent;

            while (_menuWindow->pollEvent(menuEvent))
            {
                switch (menuEvent.type)
                {
                case sf::Event::Closed:
                    _menuWindow->close();
                    break;
                case sf::Event::KeyPressed:
                    if (menuEvent.key.scancode == sf::Keyboard::Scancode::Escape)
                    {
                        if (_selectedMenu->GetRootItem())
                            _selectedMenu = _selectedMenu->GetRootItem();
                    }
                    else
                        _selectedMenu->HandleInput(menuEvent);
                    break;
                default:
                    break;
                }
            }

            _menuWindow->clear();

            if (_selectedMenu == _settingsMenu)
                ShowSettingsCheckBoxes(*_menuWindow);

            _selectedMenu->Draw(*_menuWindow);
            _menuWindow->display();
        }

        else
        {
            _game->Update();
            _game->Render();
        }
    }
}

