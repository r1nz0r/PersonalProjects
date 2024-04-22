#include "UIManager.h"
#include "Exception.h"
#include "GameSettings.h"

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

	int fontSize = 30;
	std::string initText = "Score: 0";
	_scoreLabel = new Label({ 0, 0 }, sf::Color::Cyan, _mainFont, "Score: ", fontSize);

	sf::Vector2u textCenter
	{
		GameSettings::WINDOW_SIZE.x / 2 - static_cast<uint32_t>(_scoreLabel->GetLabelHeight() * 2),
		GameSettings::UI_HUD_OFFSET_Y / 3
	};

	_scoreLabel->SetPosition(textCenter);
	UpdateScoreLabel(0);
}

UIManager::~UIManager()
{
	delete _scoreLabel;
}
