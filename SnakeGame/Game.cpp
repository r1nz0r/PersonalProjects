#include <random>
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "Exception.h"
#include "GameSettings.h"
#include "Label.h"
#include "UIManager.h"

Game::Game() : _gameField(_food, _wall)
{
	try
	{
		LoadResources();
	}
	catch (const LoadResourceException& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	Initialize();
}

void Game::LoadResources()
{
	if (!_tileSetTexture.loadFromFile(_tileSetPath))
	{
		throw LoadResourceException("Failed to load tileset texture");
	}
}

void Game::Initialize()
{
	std::srand(static_cast<unsigned>(time(nullptr)));

	_window.create(
		sf::VideoMode(GameSettings::WINDOW_SIZE.x, GameSettings::WINDOW_SIZE.y),
		GameSettings::GAME_TITLE
	);
	_currentDifficulty = EGameDifficulty::Normal;
	_window.setFramerateLimit(60); //Ограничиваем FPS для избежания слишком быстрой обработки кадров.
	_window.setKeyRepeatEnabled(false); //Отключаем повторное срабатывание сигнала при зажатии кнопки.

	_gameOverTimer.SetDuration(GameSettings::sGameEndDelay);
	_gameOverTimer.Subscribe([this]() { Start(); });

	_startTimer.SetDuration(GameSettings::sGameStartDelay);
	_startTimer.Subscribe([this]() { SwitchToPlayingState(); });

	_gameField.Initialize();
	_snake.Initialize(GetTileSetTexture());
	_food.Initialize(GetTileSetTexture(), sf::Vector2i(48, 0));
	_wall.Initialize(GetTileSetTexture(), sf::Vector2i(96, 0));
}

void Game::Start()
{
	_currentGameState = EGameState::Prepare;
	GameSettings::SetGameDifficultySettings(_currentDifficulty);
	_score = 0;
	_snake.Reset();
	_food.Respawn(GenerateFoodPosition());
	_playStopwatch.Reset();
	_startTimer.Start();
}

void Game::SwitchToPlayingState()
{
	UIManager::GetInstance().UpdateScoreLabel(_score);
	_currentGameState = EGameState::Playing;

	// Напрямую сбрасываем таймеры для корректной работы в случае когда игрок начать игру раньше
	_startTimer.Reset(); 
	_gameOverTimer.Reset();
	_playStopwatch.Start();
}

void Game::Update()
{
	ReadEvents();
	UpdateGameState();
}

void Game::Render()
{
	_window.clear();
	RenderGameState();
	_window.display();
}

void Game::UpdateGameState()
{
	switch (_currentGameState)
	{
	case EGameState::Playing:
		UpdatePlayingState();
		break;
	case EGameState::Prepare:
		UpdatePrepareState();
		break;
	case EGameState::Menu:
		//TODO menu logic
		break;
	case EGameState::Pause:
		//TODO pause logic
		break;
	case EGameState::GameOver:
		UpdateGameOverState();
		break;
	default:
		break;
	}
}

void Game::RenderGameState()
{
	switch (_currentGameState)
	{
	case EGameState::Playing:
		RenderPlayingState();
		break;
	case EGameState::Prepare:
		RenderPrepareState();
		break;
	case EGameState::Menu:
		//TODO menu logic
		break;
	case EGameState::Pause:
		RenderPauseState();
		break;
	case EGameState::GameOver:
		RenderGameOverState();
		break;
	default:
		break;
	}
}

void Game::DrawObject(IDrawable& object)
{
	object.Draw(_window);
}

void Game::UpdatePlayingState()
{
	UIManager::GetInstance().UpdatePlayTimeLabel(_playStopwatch.GetElapsedTimeSeconds());

	_snake.Update();
	const sf::Vector2u& snakePosition = _snake.GetHeadPosition();

	//Проверяем наличие коллизии. Если коллизия с стеной/змейкой то выходим из метода.
	if (HandleSnakeCollision(snakePosition))
		return;

	//Обновляем состояние игрового поля.
	UpdateGameField(snakePosition);
}

void Game::UpdateGameField(const sf::Vector2u& snakePosition)
{
	_gameField.Clear();

	try
	{
		_gameField.SetCellState(snakePosition, ECellState::SnakeHead);
		_gameField.SetCellState(_food.GetPosition(), ECellState::Food);

		for (const auto& bodyPosition : _snake.GetBodyPositions())
		{
			_gameField.SetCellState(bodyPosition, ECellState::SnakeBody);
		}
	}
	catch (const std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Game::UpdatePrepareState()
{
	_gameField.Clear();
	UIManager::GetInstance().UpdatePrepareLabel(_startTimer.GetRemainingSeconds());
	_startTimer.Update();
}

void Game::UpdateGameOverState()
{
	UIManager::GetInstance().UpdateGameOverLabel(_score);
	_gameOverTimer.Update();
}

void Game::DrawAllFieldObjects()
{
	DrawObject(_gameField);
	DrawObject(_food);
	DrawObject(_snake);
}

void Game::RenderPlayingState()
{
	DrawAllFieldObjects();
	UIManager::GetInstance().DrawPlayingHud(_window);
}

void Game::RenderPrepareState()
{
	DrawAllFieldObjects();
	UIManager::GetInstance().DrawPrepareHud(_window);
}

void Game::RenderPauseState()
{
	DrawAllFieldObjects();
	UIManager::GetInstance().DrawPauseHud(_window);
}

void Game::RenderGameOverState()
{
	UIManager::GetInstance().DrawGameOverHud(_window);
}

bool Game::HandleSnakeCollision(const sf::Vector2u& snakePosition)
{
	ECellState cellState = _gameField.GetCellState(snakePosition);

	// Обрабатываем коллизию
	switch (cellState)
	{
	case ECellState::Walls:
	case ECellState::SnakeBody:
		OnGameOver();
		return true;
	case ECellState::Food:
		OnFoodEaten();
		break;
	default:
		// Если надо - обрабатываем дефолт состояние
		break;
	}

	return false;
}

void Game::OnGameOver()
{
	_currentGameState = EGameState::GameOver;
	_gameOverTimer.Start();
}

void Game::OnWindowClosed()
{
	_window.close();
}

void Game::OnKeyPressed(const sf::Keyboard::Scancode& scancode)
{
	if (scancode == sf::Keyboard::Scancode::R)
	{
		Start();
	}
	if (scancode == sf::Keyboard::Scancode::P)
	{
		TogglePause();
	}

	if (_currentGameState == EGameState::Playing)
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

void Game::OnFoodEaten()
{
	_score += _food.Collect();
	_snake.Grow();

	sf::Vector2u newFoodPosition = GenerateFoodPosition();
	_food.Respawn(newFoodPosition);

	UIManager::GetInstance().UpdateScoreLabel(_score);
}

void Game::TogglePause()
{
	switch (_currentGameState)
	{
		case EGameState::Playing:
			Pause();
			break;
		case EGameState::Prepare:
			SwitchToPlayingState();
			break;
		case EGameState::Pause:
			UnPause();
			break;
		default:
			break;
	}
}

void Game::UnPause()
{
	_currentGameState = EGameState::Prepare;
	_startTimer.Start();
}

void Game::Pause()
{
	_currentGameState = EGameState::Pause;
	_playStopwatch.Pause();
}

uint32_t Game::GetRandomUInt(const uint32_t minValue, const uint32_t maxValue)
{
	uint32_t randomValue = std::rand();
	uint32_t right = randomValue % (maxValue - minValue + 1);
	uint32_t result = minValue + right;
	return result;
}

sf::Vector2u Game::GenerateFoodPosition()
{
	sf::Vector2u newFoodPosition;
	int tries = 0;

	do
	{
		newFoodPosition = GetRandomGridCoordinate();
		++tries;
	} while (!(_gameField.IsCellFree(newFoodPosition)));

	std::cout << "Food was moved after " << tries << " new position searches.\n";
	return newFoodPosition;
}

sf::Vector2u Game::GetRandomGridCoordinate()
{
	uint32_t minCoordinateX = GetRandomUInt(GameSettings::CELL_SIZE, GameSettings::WINDOW_SIZE.x - GameSettings::CELL_SIZE);
	minCoordinateX = minCoordinateX / GameSettings::CELL_SIZE * GameSettings::CELL_SIZE;
	uint32_t minCoordinateY = GetRandomUInt(GameSettings::CELL_SIZE, GameSettings::WINDOW_SIZE.y - GameSettings::CELL_SIZE);
	minCoordinateY = minCoordinateY / GameSettings::CELL_SIZE * GameSettings::CELL_SIZE;

	return sf::Vector2u { minCoordinateX, minCoordinateY };
}