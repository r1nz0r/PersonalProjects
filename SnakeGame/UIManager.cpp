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

	_timeLabel->SetText("Plying time: " + std::to_string(static_cast<int>(time)) + " s");
}

void UIManager::Draw(sf::RenderWindow& window)
{
	if(_scoreLabel != nullptr)
		_scoreLabel->Draw(window);
	
	if(_timeLabel != nullptr)
		_timeLabel->Draw(window);
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

	CreateHudLabels();
}

void UIManager::CreateHudLabels()
{

	uint32_t timeLabelOffset = 35;
	sf::Vector2u timeLabelPosition
	{
		timeLabelOffset,
		GameSettings::UI_HUD_OFFSET_Y / 4
	};
	_timeLabel = new Label { timeLabelPosition, sf::Color::White, _mainFont };
	
	uint32_t scoreLabelOffset = 135;
	sf::Vector2u scoreLabelPosition
	{
		GameSettings::WINDOW_SIZE.x - scoreLabelOffset,
		GameSettings::UI_HUD_OFFSET_Y / 4
	};
	_scoreLabel = new Label(scoreLabelPosition, sf::Color::Cyan, _mainFont);
}

UIManager::~UIManager()
{
	DeleteLabels();
}

void UIManager::DeleteLabels()
{
	delete _scoreLabel;
	delete _timeLabel;
}
