#include "Game.h"
#include <SFML/Window/Event.hpp>
#include "Exception.h"
#include "GameSettings.h"
#include <random>
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

	_window.setFramerateLimit(60); //Ограничиваем FPS для избежания слишком быстрой обработки кадров.
	_window.setKeyRepeatEnabled(false); //Отключаем повторное срабатывание сигнала при зажатии кнопки

	_gameField.Initialize();
	_snake.Initialize(GetTileSetTexture());
	_food.Initialize(GetTileSetTexture(), sf::Vector2i(48, 0));
	_wall.Initialize(GetTileSetTexture(), sf::Vector2i(96, 0));
}

void Game::Start()
{
	UIManager::GetInstance().UpdateScoreLabel(_score);
	_score = 0;
	_snake.Reset();
	_food.Respawn(GenerateFoodPosition());
	_snake.SetDirection(EDirection::None);
	_currentGameState = EGameState::Playing;
}

void Game::Update()
{
	float deltaTime = _clock.getElapsedTime().asSeconds();
	_clock.restart();

	ReadEvents();
	

	switch (_currentGameState)
	{
	case EGameState::Playing:
		UpdatePlayingState(deltaTime);
		break;
	case EGameState::Menu:
		//TODO menu logic
		break;
	case EGameState::Pause:
		//TODO pause logic
		break;
	case EGameState::GameOver:
		//TODO game over logic
		break;
	default:
		break;
	}
}

void Game::Render()
{
	_window.clear();

	switch (_currentGameState)
	{
	case EGameState::Playing:
		RenderPlayingState();
		break;
	case EGameState::Menu:
		//TODO menu logic
		break;
	case EGameState::Pause:
		//TODO pause logic
		break;
	case EGameState::GameOver:
		//TODO game over logic
		break;
	default:
		break;
	}

	if (_printTimer.getElapsedTime().asSeconds() >= GameSettings::sTimePerCell)
	{
		_gameField.Print();
		_printTimer.restart();
	}

	_window.display();
}

void Game::DrawObject(IDrawable& object)
{
	object.Draw(_window);
}

void Game::UpdatePlayingState(const float deltaTime)
{
	_snake.Update(deltaTime);
	auto snakePosition = _snake.GetHeadPosition();

	if (ECellState collisionSellState = ECellState::Empty; CheckSnakeCollision(collisionSellState))
	{
		OnCollisionEnter(collisionSellState);
	}

	//Сбрасываем все клетки поля в исходное состояние.
	//Обязательно делать это ПОСЛЕ проверки на коллизию, иначе проверяться будут пустые клетки.
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

void Game::RenderPlayingState()
{
	DrawObject(_gameField);
	DrawObject(_snake);
	DrawObject(_food);

	const Label* scoreLabel = UIManager::GetInstance().GetScoreLabel();

	if (scoreLabel != nullptr)
	{
		Label tempLabel = *scoreLabel;
		DrawObject(tempLabel);
	}
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

void Game::OnCollisionEnter(const ECellState collisionCellState)
{
	switch (collisionCellState)
	{
	case ECellState::Walls:
	case ECellState::SnakeBody:
		_currentGameState = EGameState::Pause;
		break;
	case ECellState::Food:
		OnFoodEaten();
		break;
	default:
		break;
	}
}

void Game::OnWindowClosed()
{
	_window.close();
}

void Game::OnKeyPressed(const sf::Keyboard::Scancode& scancode)
{
	if (scancode == sf::Keyboard::Scancode::P)
	{
		Start();
	}

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
	//return minValue + std::rand() % (maxValue - minValue + 1);
}

sf::Vector2u Game::GenerateFoodPosition()
{
	sf::Vector2u newFoodPosition;
	int tries = 1;

	while (!(GetFreeGridPosition(newFoodPosition)))
	{
		uint32_t minCoordinateX = GetRandomUInt(GameSettings::CELL_SIZE, GameSettings::WINDOW_SIZE.x - GameSettings::CELL_SIZE);
		minCoordinateX = minCoordinateX / GameSettings::CELL_SIZE * GameSettings::CELL_SIZE;
		uint32_t minCoordinateY = GetRandomUInt(GameSettings::CELL_SIZE, GameSettings::WINDOW_SIZE.y - GameSettings::CELL_SIZE);
		minCoordinateY = minCoordinateY / GameSettings::CELL_SIZE * GameSettings::CELL_SIZE;

		newFoodPosition = sf::Vector2u { minCoordinateX, minCoordinateY };
		++tries;
	}

	std::cout << "Food was moved after " << tries << " new position searches.";
	return newFoodPosition;
}