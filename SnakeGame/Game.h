#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Food.h"
#include "GameField.h"
#include "Graphics.h"
#include "Snake.h"
#include "SnakeController.h"
#include "Walls.h"

enum class EGameState
{
    Playing,
    Pause,
    Menu,
    GameOver,
    None
};

class Game
{
public:
    Game();
    ~Game() = default;
    const sf::Texture& GetTileSetTexture() const { return _tileSetTexture; }
    void LoadResources();
    void Start();
    void Update();

private:
    const std::string _tileSetPath = R"(Resources/Textures/snake.png)";
    EGameState _currentGameState = EGameState::None;
    sf::Texture _tileSetTexture;
    sf::RenderWindow _window;
    sf::Clock _clock;
    Graphics _graphics;
    GameField _gameField;
    Snake _snake;
    SnakeController _snakeController {_snake};
    std::vector<Wall> _walls;
    Food _food;

    void OnWindowClosed();
    void OnKeyPressed(const sf::Keyboard::Scancode& scancode);
    void ReadEvents();
};
