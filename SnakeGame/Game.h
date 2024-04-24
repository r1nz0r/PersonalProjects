#pragma once
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Food.h"
#include "GameField.h"
#include "Snake.h"
#include "SnakeController.h"
#include "Walls.h"
#include "Stopwatch.h"
#include "Timer.h"

enum class EGameDifficulty;

enum class EGameState
{
	Playing,
	Prepare,
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
	void Render();
	bool IsWindowOpen() const { return _window.isOpen(); }
	int GetScore() const { return _score; }

private:
	const std::string _tileSetPath = R"(Resources/Textures/snake.png)";
	EGameState _currentGameState = EGameState::None;
	sf::Texture _tileSetTexture;
	sf::RenderWindow _window;
	sf::Clock _deltaTimeClock; // Счетчик времени между кадрами
	GameField _gameField;
	Snake _snake;
	SnakeController _snakeController { _snake };
	Wall _wall;
	Food _food;

	Stopwatch _playStopwatch; // Счетчик времени от начала игровой сессии.
	Timer _startTimer; // Таймер для задержки начала игры.
	Timer _gameOverTimer; // Таймер для задержки конца игры.

	int _score;
	EGameDifficulty _currentDifficulty;

	void Initialize();
	void DrawObject(IDrawable& object);
	void UpdatePlayingState();
	void UpdateGameField(sf::Vector2u& snakePosition);
	void UpdatePrepareState();
	void UpdateGameOverState();
	void SwitchToPlayingState();
	void DrawFieldAndFood();
	void RenderPlayingState();
	void RenderPrepareState();
	void RenderGameOverState();
	bool CheckSnakeCollision(ECellState& collisionCellState);
	void OnGameOver();
	void OnWindowClosed();
	void OnKeyPressed(const sf::Keyboard::Scancode& scancode);
	void ReadEvents();
	void OnFoodEaten();
	void TogglePause();
	bool GetFreeGridPosition(sf::Vector2u& position);
	uint32_t GetRandomUInt(const uint32_t minValue, const uint32_t maxValue);
	sf::Vector2u GenerateFoodPosition();
};
