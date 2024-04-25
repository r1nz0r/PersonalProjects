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
	void UpdateGameState();
	void Render();
	void RenderGameState();
	bool IsWindowOpen() const { return _window.isOpen(); }
	int GetScore() const { return _score; }

private:
	const std::string _tileSetPath = R"(Resources/Textures/snake.png)";
	EGameState _currentGameState = EGameState::None;
	sf::Texture _tileSetTexture;
	sf::RenderWindow _window;
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
	void UpdateGameField(const sf::Vector2u& snakePosition);
	void UpdatePrepareState();
	void UpdateGameOverState();
	void SwitchToPlayingState();
	void DrawFieldAndFood();
	void RenderPlayingState();
	void RenderPrepareState();
	void RenderPauseState();
	void RenderGameOverState();
	bool HandleSnakeCollision(const sf::Vector2u& snakePosition);
	void OnGameOver();
	void OnWindowClosed();
	void OnKeyPressed(const sf::Keyboard::Scancode& scancode);
	void ReadEvents();
	void OnFoodEaten();
	void TogglePause();
	void UnPause();
	void Pause();
	uint32_t GetRandomUInt(const uint32_t minValue, const uint32_t maxValue);
	sf::Vector2u GenerateFoodPosition();
	sf::Vector2u GetRandomGridCoordinate();
};
