﻿#include <random>
#include <fstream>
#include <algorithm>
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "Exception.h"
#include "GameSettings.h"
#include "Text.h"
#include "UIManager.h"
#include "Menu.h"
#include "Application.h"
#include "AudioPlayer.h"

Game::Game() : _gameField(_food, _wall), _score(0), _recordsTable()
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
	DeserializeGame();

	_window.create(
		sf::VideoMode(GameSettings::WINDOW_SIZE.x, GameSettings::WINDOW_SIZE.y),
		GameSettings::GAME_TITLE,
		sf::Style::Close
	);
	_currentDifficulty = EGameDifficulty::Normal;
	GameSettings::SetGameDifficultySettings(_currentDifficulty);
	_window.setFramerateLimit(60); //Ограничиваем FPS для избежания слишком быстрой обработки кадров.
	_window.setKeyRepeatEnabled(false); //Отключаем повторное срабатывание сигнала при зажатии кнопки.

	_gameOverTimer.SetDuration(GameSettings::sGameEndDelay);
	_gameOverTimer.onTimerFired += std::bind(&Game::Start, this);

	_startTimer.SetDuration(GameSettings::sGameStartDelay);
	_startTimer.onTimerFired += std::bind(&Game::SwitchToPlayingState, this);

	_gameField.Initialize();
	_snake.Initialize(GetTileSetTexture());
	_food.Initialize(GetTileSetTexture(), sf::Vector2i(48, 0));
	_wall.Initialize(GetTileSetTexture(), sf::Vector2i(96, 0));

	_window.setVisible(false);

	Menu::ItemsList mainMenuItems
	{
		{"Continue", [this]() { std::cout << "Continue game selected!" << std::endl; UnPause(); }},
		{"Exit", [this]() { std::cout << "Exit game selected!" << std::endl; ExitGame(); }}
	};
	_pauseMenu = new Menu { mainMenuItems, UIManager::GetInstance().GetFont() , _window, "Pause" };
}

void Game::Start()
{
	_window.setVisible(true);
	_currentGameState = EGameState::Prepare;
	GameSettings::SetGameDifficultySettings(_currentDifficulty);
	_score = 0;
	_snake.Reset();
	_food.Respawn(GenerateFoodPosition());
	_playStopwatch.Reset();
	_startTimer.Start();
	AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Theme);
}

void Game::SwitchToPlayingState()
{
	UIManager::GetInstance().UpdateScoreText(_score);
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
	case EGameState::Pause:
		//Просто скипаем, меню обрабатывает UI.
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
		DrawAllFieldObjects();
		UIManager::GetInstance().DrawPlayingHud(_window);
		break;
	case EGameState::Prepare:
		DrawAllFieldObjects();
		UIManager::GetInstance().DrawPrepareHud(_window);
		break;
	case EGameState::Pause:
		DrawAllFieldObjects();
		UIManager::GetInstance().DrawPauseHud(_window, _pauseMenu);
		break;
	case EGameState::GameOver:
		UIManager::GetInstance().DrawGameOverHud(_window);
		break;
	default:
		break;
	}
}

void Game::SetDifficulty(EGameDifficulty difficulty)
{
	_currentDifficulty = difficulty;
}

void Game::ExitGame()
{
	_window.setActive(false);
	_window.setVisible(false);
	AudioPlayer::GetInstance().StopMusic();
	UIManager::GetInstance().SetMenuOpen(true);
}

void Game::DrawObject(IDrawable& object)
{
	object.Draw(_window);
}

void Game::UpdatePlayingState()
{
	UIManager::GetInstance().UpdatePlayTimeText(_playStopwatch.GetElapsedTimeSeconds());

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
	UIManager::GetInstance().UpdatePrepareText(_startTimer.GetRemainingSeconds());
	_startTimer.Update();
}

void Game::UpdateGameOverState()
{
	if (UIManager::GetInstance().IsMenuOpen())
		return;

	_gameOverTimer.Update();
}

void Game::UpdateRecordsTable()
{
	int maxScoresPerScreen = 10;
	_recordsTable.insert({ _playerName, _score });

	if (_recordsTable.size() > maxScoresPerScreen)
	{
		auto it = _recordsTable.end();
		std::advance(it, -std::distance(_recordsTable.begin(), _recordsTable.end()) + maxScoresPerScreen);
		_recordsTable.erase(it, _recordsTable.end());
	}

	UIManager::GetInstance().UpdateGameOverLabel(_score, _recordsTable.rbegin()->score);
	SerializeGame();
}

void Game::DrawAllFieldObjects()
{
	DrawObject(_gameField);
	DrawObject(_food);
	DrawObject(_snake);
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
	AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Hit);	
	_currentGameState = EGameState::GameOver;

	if (_recordsTable.empty() || _score > _recordsTable.rbegin()->score)
	{
		UIManager::GetInstance().ShowNewRecordMenu();		
	}
	else
	{
		StartGameOverState();
		UIManager::GetInstance().UpdateGameOverLabel(_score, _recordsTable.rbegin()->score);
	}

}

void Game::StartGameOverState()
{
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
	if (scancode == sf::Keyboard::Scancode::Escape)
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
			if (_currentGameState == EGameState::Pause)
				_pauseMenu->HandleInput(event);
			else
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
	AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Eat);
	_score += _food.Collect();
	_snake.Grow();

	sf::Vector2u newFoodPosition = GenerateFoodPosition();
	_food.Respawn(newFoodPosition);

	UIManager::GetInstance().UpdateScoreText(_score);
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

bool Game::SerializeGame()
{
	std::ofstream fileOutput(GameSettings::RECORDS_TABLE_FILE_NAME);
	
	if (!fileOutput.is_open())
	{
		std::cerr << "Cant open file " << GameSettings::RECORDS_TABLE_FILE_NAME << " for write.";
		return false;
	}

	for (const auto& record : _recordsTable)
	{
		fileOutput << record.name << " " << record.score << std::endl;
	}

	fileOutput.close();
	return true;
}

bool Game::DeserializeGame()
{
	std::ifstream fileInput(GameSettings::RECORDS_TABLE_FILE_NAME);

	if (!fileInput.is_open())
	{
		std::cerr << "Cant open file " << GameSettings::RECORDS_TABLE_FILE_NAME << " for read.";
		return false;
	}

	std::string name;
	int score;

	while (fileInput >> name >> score)
	{
		_recordsTable.insert(PlayerScore(name, score));
	}

	fileInput.close();
	return true;
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