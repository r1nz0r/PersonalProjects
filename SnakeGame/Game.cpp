#include "Game.h"
#include <SFML/Window/Event.hpp>
#include "Exception.h"
#include "GameSettings.h"

Game::Game() : _graphics(_window)
{    
    try
    {
        LoadResources();
    }
    catch (const LoadResourceException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Game::LoadResources()
{
    if (!_tileSetTexture.loadFromFile(_tileSetPath))
    {
        throw LoadResourceException("Failed to load tileset texture");
    }
}

void Game::Start()
{
    _window.create(
        sf::VideoMode(GameSettings::WINDOW_SIZE.x, GameSettings::WINDOW_SIZE.y),
        GameSettings::GAME_TITLE
    );
    _window.setFramerateLimit(60); //Ограничиваем FPS для избежания слишком быстрой обработки кадров.
    _window.setKeyRepeatEnabled(false);
    _snake.Initialize(GetTileSetTexture());
}

void Game::Update()
{
    while (_window.isOpen())
    {
        float deltaTime = _clock.getElapsedTime().asSeconds();
        _clock.restart();
        ReadEvents();
        
        _window.clear();
        _graphics.DrawObject(_snake);
        _window.display();
    }
}

void Game::OnWindowClosed()
{
    _window.close();
}

void Game::OnKeyPressed(const sf::Keyboard::Scancode& scancode)
{
    _snakeController.HandleInput(scancode);
}

void Game::ReadEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            OnWindowClosed();
            break;
        case sf::Event::KeyPressed:
            OnKeyPressed(event.key.scancode);
            break;
        default:
            //Остальные события нас не интересуют
            break;
        }
    }
}
