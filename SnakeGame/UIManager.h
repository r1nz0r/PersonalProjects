#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Label.h"

class UIManager
{
public:
	static UIManager& GetInstance();

	UIManager(const UIManager& other) = delete;
	UIManager(UIManager&& other) noexcept = delete;
	UIManager& operator=(const UIManager& other) = delete;
	UIManager& operator=(UIManager&& other) noexcept = delete;

	void ShowMainMenu();
	void UpdateScoreLabel(const int score);
	const Label* const GetScoreLabel() const { return _scoreLabel; }
	void ShowDifficultyMenu();
	void ShowHighScoresMenu();
	void ShowSettingsMenu();
	void Update();
	void HandleInput();

private:
	UIManager();
	~UIManager();
	const std::string _fontPath = R"(Resources/Fonts/Accuratist.ttf)";
	sf::Font _mainFont;
	Label* _scoreLabel = nullptr;
};