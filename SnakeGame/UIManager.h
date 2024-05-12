#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextBlock;
class Text;
class Menu;

class UIManager
{
public:
	static UIManager& GetInstance();

	UIManager(const UIManager& other) = delete;
	UIManager(UIManager&& other) noexcept = delete;
	UIManager& operator=(const UIManager& other) = delete;
	UIManager& operator=(UIManager&& other) noexcept = delete;

	void ShowMainMenu();
	void UpdateScoreText(const int score);
	void UpdatePlayTimeText(const float time);
	void UpdatePrepareText(const float time);
	void UpdateGameOverLabel(const int score, const int highScore);
	const Text* const GetScoreText() const { return _scoreText; }
	void ShowDifficultyMenu();
	void ShowHighScoresMenu();
	void ShowSettingsMenu();
	void Update();
	void HandleInput();
	void DrawPlayingHud(sf::RenderWindow& window);
	void DrawPauseHud(sf::RenderWindow& window, Menu* pauseMenu);
	void DrawPrepareHud(sf::RenderWindow& window);
	void DrawGameOverHud(sf::RenderWindow& window);
	void DrawBackground(sf::RenderWindow& window, const sf::Color& color);
	const sf::Font& GetFont() const { return _mainFont; }
private:
	UIManager();
	void CreateHudLabels();
	~UIManager();
	void DeleteLabels();
	const std::string _fontPath = R"(Resources/Fonts/Accuratist.ttf)";
	sf::Font _mainFont;
	Text* _scoreText = nullptr;
	Text* _timeText = nullptr;
	TextBlock* _gameOverBlock = nullptr;
	sf::RectangleShape _background;
};