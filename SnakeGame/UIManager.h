#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextBlock;
class Text;
class Menu;
class TextInputBox;

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
	void ShowHighScoresMenu();
	void Update();
	void HandleInput(const sf::Event& menuEvent);
	void DrawPlayingHud(sf::RenderWindow& window);
	void DrawPauseHud(sf::RenderWindow& window, Menu* pauseMenu);
	void DrawPrepareHud(sf::RenderWindow& window);
	void DrawGameOverHud(sf::RenderWindow& window);
	void DrawBackground(sf::RenderWindow& window, const sf::Color& color);
	void SetMenuOpen(bool flag);
	const sf::Font& GetFont() const { return _mainFont; }
	const sf::RenderWindow& GetMenuWindow() const { return *_menuWindow; }
	bool IsMenuOpen() const { return _bIsMenuOpen; }
private:
	UIManager();
	void CreateHudLabels();
	~UIManager();
	void Clear();
	const std::string _fontPath = R"(Resources/Fonts/Accuratist.ttf)";
	sf::Font _mainFont;
	Text* _scoreText = nullptr;
	Text* _timeText = nullptr;
	TextBlock* _gameOverBlock = nullptr;
	sf::RectangleShape _background;
	Menu* _selectedMenu;
	Menu* _mainMenu;
	Menu* _difficultyMenu;
	Menu* _settingsMenu;
	bool _bIsMenuOpen;
	TextInputBox* _soundCheck;
	TextInputBox* _musicCheck;
	sf::RenderWindow* _menuWindow;
	void ShowSettingsCheckBoxes(sf::RenderWindow& window);
	void CreateSettingsCheckBoxes();
	void CreateMenuItems();
	void ToggleCheckbox(TextInputBox* checkBox);
};