#include <iomanip>
#include <sstream>
#include "UIManager.h"
#include "Exception.h"
#include "GameSettings.h"
#include "Time.h"
#include "Game.h"
#include "TextBlock.h"
#include "Menu.h"

UIManager& UIManager::GetInstance()
{
	static UIManager sUiManager;
	return sUiManager;
}

void UIManager::ShowMainMenu()
{

}

void UIManager::UpdateScoreText(const int score)
{
	if (!_scoreText)
		return;

	_scoreText->setString("Score: " + std::to_string(score));
}

void UIManager::UpdatePlayTimeText(const float time)
{
	if (!_timeText)
		return;

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << time;
	_timeText->setString("Playing time: " + oss.str() + " s");

	float timeLabelOffsetX = 35.0f;
	sf::Vector2f timeLabelPosition
	{
		timeLabelOffsetX,
		GameSettings::UI_HUD_OFFSET_Y / 4.0f
	};
	_timeText->setPosition(timeLabelPosition);
}

void UIManager::UpdatePrepareText(const float time)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << time;
	_timeText->setString("Get ready! " + oss.str());
	
	sf::Vector2f timeLabelPosition
	{
		(GameSettings::WINDOW_SIZE.x - _timeText->getLocalBounds().width) / 2.0f,
		GameSettings::WINDOW_SIZE.y / 3.0f
	};
	_timeText->setPosition(timeLabelPosition);
}

void UIManager::UpdateGameOverLabel(const int score, const int highScore)
{
	if (!_gameOverBlock)
		return;

	_gameOverBlock->Clear();
	_gameOverBlock->AddText(std::string("Game Over!"), _mainFont);
	_gameOverBlock->AddText(std::string("Your score is - " + std::to_string(score)), _mainFont);
	_gameOverBlock->AddText(std::string("High score is - " + std::to_string(highScore)), _mainFont);
	_gameOverBlock->AlignTexts();
}

void UIManager::DrawPlayingHud(sf::RenderWindow& window)
{
	if (_scoreText != nullptr)
		_scoreText->Draw(window);

	if (_timeText != nullptr)
		_timeText->Draw(window);
}

void UIManager::DrawPrepareHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sPrepareBackgroundColor);

	if (_timeText != nullptr)
		_timeText->Draw(window);
}

void UIManager::DrawPauseHud(sf::RenderWindow& window, Menu* pauseMenu)
{
	DrawBackground(window, GameSettings::sPauseBackgroundColor);

	if (!pauseMenu)
		return;

	pauseMenu->Draw(window);
}

void UIManager::DrawGameOverHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sGameOverBackgroundColor);

	if (_gameOverBlock != nullptr)
		_gameOverBlock->Draw(window);
}

void UIManager::DrawBackground(sf::RenderWindow& window, const sf::Color& color)
{
	_background.setFillColor(sf::Color(color));
	window.draw(_background);
}

UIManager::UIManager()
{
	try
	{
		_mainFont.loadFromFile(_fontPath);
	}
	catch (const LoadResourceException& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	_background.setSize(sf::Vector2f(GameSettings::WINDOW_SIZE.x, GameSettings::WINDOW_SIZE.y));
	_background.setFillColor(sf::Color(10, 20, 40, 230)); // Little transparent dark blue color.

	CreateHudLabels();
}

void UIManager::CreateHudLabels()
{
	_timeText = new Text {"", _mainFont, sf::Color::White};
	_gameOverBlock = new TextBlock
	{
		sf::Vector2f(GameSettings::WINDOW_SIZE.x / 2, GameSettings::WINDOW_SIZE.x / 2),
		10 
	};

	float scoreLabelOffsetX = 145.0f;
	sf::Vector2f scoreTextPosition
	{
		GameSettings::WINDOW_SIZE.x - scoreLabelOffsetX,
		GameSettings::UI_HUD_OFFSET_Y / 4.0
	};

	_scoreText = new Text { "", _mainFont, sf::Color::Cyan };
	_scoreText->setPosition(scoreTextPosition);
	
}

UIManager::~UIManager()
{
	DeleteLabels();
}

void UIManager::DeleteLabels()
{
	delete _scoreText;
	delete _timeText;
	delete _gameOverBlock;
}