#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Label;

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
	void UpdatePlayTimeLabel(const float time);
	void UpdatePrepareLabel(const float time);
	void UpdateGameOverLabel(const int score);
	const Label* const GetScoreLabel() const { return _scoreLabel; }
	void ShowDifficultyMenu();
	void ShowHighScoresMenu();
	void ShowSettingsMenu();
	void Update();
	void HandleInput();
	void DrawPlayingHud(sf::RenderWindow& window);
	void DrawPauseHud(sf::RenderWindow& window);
	void DrawPrepareHud(sf::RenderWindow& window);
	void DrawGameOverHud(sf::RenderWindow& window);
	void DrawBackground(sf::RenderWindow& window, const sf::Color& color);

private:
	UIManager();
	void CreateHudLabels();
	~UIManager();
	void DeleteLabels();
	const std::string _fontPath = R"(Resources/Fonts/Accuratist.ttf)";
	sf::Font _mainFont;
	Label* _scoreLabel = nullptr;
	Label* _timeLabel = nullptr;
	Label* _pauseLabel = nullptr;
	Label* _gameOverLabel = nullptr;
	sf::RectangleShape _background;
};