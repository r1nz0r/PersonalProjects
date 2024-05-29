#pragma once
#include <string>
#include <set>
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
	GameOver,
	None
};

class Menu;

struct PlayerScore
{
	std::string name;
	int score;

	PlayerScore(const std::string& name_, int score_) : name(name_), score(score_) {}
};

struct CompareScores
{
	bool operator()(const PlayerScore& a, const PlayerScore& b) const
	{
		if (a.score == b.score)
		{
			return a.name < b.name; // Для уникальности при одинаковых очках
		}

		return a.score > b.score; // Сортировка по убыванию очков
	}
};

class Game
{
public:
	using RecordsTable = std::multiset<PlayerScore, CompareScores>;

	Game();
	~Game() = default;
	const sf::Texture& GetTileSetTexture() const { return _tileSetTexture; }
	void LoadResources();
	void Initialize();
	void Start();
	void Update();
	void UpdateGameState();
	void Render();
	void RenderGameState();
	RecordsTable GetRecordsTable() const { return _recordsTable; }
	void SetDifficulty(EGameDifficulty difficulty);
	void ExitGame();
	bool IsWindowOpen() const { return _window.isOpen(); }
	int GetScore() const { return _score; }
	void SetPlayerName(const std::string& name) { _playerName = name; };
	std::string GetPlayerName() const { return _playerName; }
	void UpdateRecordsTable();
	void StartGameOverState();
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

	EGameDifficulty _currentDifficulty;
	int _score;
	RecordsTable _recordsTable;
	std::string _playerName;

	Menu* _pauseMenu = nullptr;

	void DrawObject(IDrawable& object);
	void UpdatePlayingState();
	void UpdateGameField(const sf::Vector2u& snakePosition);
	void UpdatePrepareState();
	void UpdateGameOverState();
	void SwitchToPlayingState();
	void DrawAllFieldObjects();
	bool HandleSnakeCollision(const sf::Vector2u& snakePosition);
	void OnGameOver();
	void OnWindowClosed();
	void OnKeyPressed(const sf::Keyboard::Scancode& scancode);
	void ReadEvents();
	void OnFoodEaten();
	void TogglePause();
	void UnPause();
	bool SerializeGame();
	bool DeserializeGame();
	void Pause();
	uint32_t GetRandomUInt(const uint32_t minValue, const uint32_t maxValue);
	sf::Vector2u GenerateFoodPosition();
	sf::Vector2u GetRandomGridCoordinate();
};
