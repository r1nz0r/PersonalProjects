#include <iomanip>
#include <sstream>
#include "UIManager.h"
#include "Exception.h"
#include "GameSettings.h"
#include "Label.h"
#include "Game.h"

UIManager& UIManager::GetInstance()
{
	static UIManager sUiManager;
	return sUiManager;
}

void UIManager::ShowMainMenu()
{

}

void UIManager::UpdateScoreLabel(const int score)
{
	if (!_scoreLabel)
		return;

	_scoreLabel->SetText("Score: " + std::to_string(score));
}

void UIManager::UpdatePlayTimeLabel(const float time)
{
	if (!_timeLabel)
		return;

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << time;
	_timeLabel->SetText("Playing time: " + oss.str() + " s");

	uint32_t timeLabelOffsetX = 35;
	sf::Vector2u timeLabelPosition
	{
		timeLabelOffsetX,
		GameSettings::UI_HUD_OFFSET_Y / 4
	};
	_timeLabel->SetPosition(timeLabelPosition);
}

void UIManager::UpdatePrepareLabel(const float time)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << time;
	_timeLabel->SetText("Get ready! " + oss.str());
	
	sf::Vector2u timeLabelPosition
	{
		(GameSettings::WINDOW_SIZE.x - static_cast<uint32_t>(_timeLabel->GetLabelWidth())) / 2,
		GameSettings::WINDOW_SIZE.y / 3
	};
	_timeLabel->SetPosition(timeLabelPosition);
}

void UIManager::UpdateGameOverLabel(const int score)
{
	if (!_gameOverLabel)
		return;

	std::string gameOverText = "Game Over!\nYour score is - " + std::to_string(score) + "\nHigh score is - 0000";
	_gameOverLabel->SetText(gameOverText);

	sf::Vector2u gameOverLabelPosition
	{
		(GameSettings::WINDOW_SIZE.x - static_cast<uint32_t>(_gameOverLabel->GetLabelWidth())) / 2,
		(GameSettings::WINDOW_SIZE.y - static_cast<uint32_t>(_gameOverLabel->GetLabelHeight())) / 2
	};
	_gameOverLabel->SetPosition(gameOverLabelPosition);
}

void UIManager::DrawPlayingHud(sf::RenderWindow& window)
{
	if (_scoreLabel != nullptr)
		_scoreLabel->Draw(window);

	if (_timeLabel != nullptr)
		_timeLabel->Draw(window);
}

void UIManager::DrawPrepareHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sPrepareBackgroundColor);

	if (_timeLabel != nullptr)
		_timeLabel->Draw(window);
}

void UIManager::DrawPauseHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sPauseBackgroundColor);

	if (_pauseLabel != nullptr)
		_pauseLabel->Draw(window);
}

void UIManager::DrawGameOverHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sGameOverBackgroundColor);

	if (_gameOverLabel != nullptr)
		_gameOverLabel->Draw(window);
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
	_timeLabel = new Label { {0,0 }, sf::Color::White, _mainFont };
	_gameOverLabel = new Label({ 0,0 }, sf::Color::White, _mainFont, "", 40u);

	uint32_t scoreLabelOffsetX = 145;
	sf::Vector2u scoreLabelPosition
	{
		GameSettings::WINDOW_SIZE.x - scoreLabelOffsetX,
		GameSettings::UI_HUD_OFFSET_Y / 4
	};
	_scoreLabel = new Label(scoreLabelPosition, sf::Color::Cyan, _mainFont);

	_pauseLabel = new Label({ 0,0 }, sf::Color::Red, _mainFont, "PAUSE", 50u);
	sf::Vector2u pauseLabelPosition
	{
		(GameSettings::WINDOW_SIZE.x - static_cast<uint32_t>(_pauseLabel->GetLabelWidth())) / 2,
		(GameSettings::WINDOW_SIZE.y - static_cast<uint32_t>(_pauseLabel->GetLabelHeight())) / 2
	};
	_pauseLabel->SetPosition(pauseLabelPosition);
}

UIManager::~UIManager()
{
	DeleteLabels();
}

void UIManager::DeleteLabels()
{
	delete _scoreLabel;
	delete _timeLabel;
	delete _pauseLabel;
	delete _gameOverLabel;
}