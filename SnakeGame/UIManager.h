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
	void ShowNewRecordMenu();
	void UpdateScoreText(const int score);
	void UpdatePlayTimeText(const float time);
	void UpdatePrepareText(const float time);
	void UpdateGameOverLabel(const int score, const int highScore);
	const Text* const GetScoreText() const { return _scoreText; }
	void Update();
	void HandleInput(const sf::Event& menuEvent);
	void ProcessUserTextInput(const sf::Event& menuEvent);
	void OnEscapePressed();
	void DrawPlayingHud(sf::RenderWindow& window);
	void DrawPauseHud(sf::RenderWindow& window, Menu* pauseMenu);
	void DrawPrepareHud(sf::RenderWindow& window);
	void DrawGameOverHud(sf::RenderWindow& window);
	void DrawBackground(sf::RenderWindow& window, const sf::Color& color);
	void SetMenuOpen(bool flag);
	const sf::Font& GetFont() const { return _mainFont; }
	bool IsMenuOpen() const { return _bIsMenuOpen; }
private:
	UIManager();
	~UIManager();

	void CreateHudLabels();
	void Clear();
	void ShowSettingsCheckBoxes(sf::RenderWindow& window);
	void CreateSettingsCheckBoxes();
	void CreateMenuItems();
	void ToggleCheckbox(TextInputBox* checkBox);
	void CreateMenuRecordsTable();
	const std::string _fontPath = R"(Resources/Fonts/Accuratist.ttf)";
	sf::Font _mainFont;
	sf::RectangleShape _background;
	Text* _scoreText = nullptr;
	Text* _timeText = nullptr;
	TextBlock* _gameOverBlock = nullptr;
	Menu* _recordsMenu = nullptr;
	Menu* _selectedMenu = nullptr;
	Menu* _mainMenu = nullptr;
	Menu* _difficultyMenu = nullptr;
	Menu* _enterNameDialog = nullptr;
	Menu* _settingsMenu = nullptr;
	TextInputBox* _nameInputBox = nullptr;
	TextInputBox* _soundCheck = nullptr;
	TextInputBox* _musicCheck = nullptr;
	sf::RenderWindow* _menuWindow = nullptr;
	bool _bIsMenuOpen;
	bool _bIsInputActive;
};