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
	_startTimer.Start();
}

void Game::SwitchToPlayingState()
{
	UIManager::GetInstance().UpdateScoreLabel(0);
	UIManager::GetInstance().UpdatePlayTimeLabel(0.0f);
	_currentGameState = EGameState::Playing;
	_playStopwatch.Restart();
}

void Game::Update()
{
	ReadEvents();

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

	Render();
}

void Game::Render()
{
	_window.clear();

	switch (_currentGameState)
	{
	case EGameState::Playing:
		RenderPlayingState();
		break;
	case EGameState::Prepare:
		RenderPrepareState();
	case EGameState::Menu:
		//TODO menu logic
		break;
	case EGameState::Pause:
		RenderPlayingState();
		break;
	case EGameState::GameOver:
		RenderGameOverState();
		break;
	default:
		break;
	}

	_window.display();
}

void Game::DrawObject(IDrawable& object)
{
	object.Draw(_window);
}

void Game::UpdatePlayingState()
{
	float deltaTime = _deltaTimeClock.getElapsedTime().asSeconds();
	_deltaTimeClock.restart();

	UIManager::GetInstance().UpdatePlayTimeLabel(_playStopwatch.GetElapsedTimeSeconds());
	_snake.Update(deltaTime);

	auto snakePosition = _snake.GetHeadPosition();

	ECellState collisionCellState = ECellState::Empty;
	bool isCollisionDetected = CheckSnakeCollision(collisionCellState);

	if (isCollisionDetected)
	{
		switch (collisionCellState)
		{
		case ECellState::Walls:
		case ECellState::SnakeBody:
			OnGameOver();
			return;
		case ECellState::Food:
			OnFoodEaten();
			break;
		default:
			break;
		}
	}

	//Обновляем состояние игрового поля.
	UpdateGameField(snakePosition);
}

void Game::UpdateGameField(sf::Vector2u& snakePosition)
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
	_startTimer.Update();
}

void Game::UpdateGameOverState()
{
	_gameOverTimer.Update();
}

void Game::DrawFieldAndFood()
{
	DrawObject(_gameField);
	DrawObject(_food);
}

void Game::RenderPlayingState()
{
	DrawFieldAndFood();
	DrawObject(_snake);
	UIManager::GetInstance().Draw(_window);
}

void Game::RenderPrepareState()
{
	DrawFieldAndFood();
	DrawObject(_snake);
}

void Game::RenderGameOverState()
{
	DrawFieldAndFood();
}

bool Game::CheckSnakeCollision(ECellState& collisionCellState)
{
	const auto& currentSnakePosition = _snake.GetHeadPosition();
	const ECellState snakeHeadPositionCellState = _gameField.GetCellState(currentSnakePosition);

	if (snakeHeadPositionCellState == ECellState::Empty)
	{
		return false;
	}

	collisionCellState = snakeHeadPositionCellState;
	return true;
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
	if (_currentGameState == EGameState::Playing)
	{
		_currentGameState = EGameState::Pause;
		_playStopwatch.Pause();
	}
	else
	{
		_currentGameState = EGameState::Playing;
		_playStopwatch.Start();
	}
}

bool Game::GetFreeGridPosition(sf::Vector2u& position)
{
	auto cellState = _gameField.GetCellState(position);

	if (cellState == ECellState::Empty)
		return true;

	return false;
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

	while (!(GetFreeGridPosition(newFoodPosition)))
	{
		uint32_t minCoordinateX = GetRandomUInt(GameSettings::CELL_SIZE, GameSettings::WINDOW_SIZE.x - GameSettings::CELL_SIZE);
		minCoordinateX = minCoordinateX / GameSettings::CELL_SIZE * GameSettings::CELL_SIZE;
		uint32_t minCoordinateY = GetRandomUInt(GameSettings::CELL_SIZE, GameSettings::WINDOW_SIZE.y - GameSettings::CELL_SIZE);
		minCoordinateY = minCoordinateY / GameSettings::CELL_SIZE * GameSettings::CELL_SIZE;

		newFoodPosition = sf::Vector2u { minCoordinateX, minCoordinateY };
		++tries;
	}

	std::cout << "Food was moved after " << tries << " new position searches.\n";
	return newFoodPosition;
}