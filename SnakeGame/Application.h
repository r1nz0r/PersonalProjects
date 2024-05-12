#pragma once
#include "SFML/Graphics.hpp"
class Game;
class Menu;
class TextInputBox;
class Application
{
public:
	Application(const Application& other) = delete;
	Application(Application&& other) noexcept = delete;
	Application& operator=(const Application& other) = delete;
	Application& operator=(Application&& other) = delete;

	static Application& GetInstance();
	void Run();
	void Clear();
	void SetMenuOpen(bool flag);
	const Game* GetGame() const { return _game; }

private:
	Game* _game;
	Menu* _selectedMenu;
	Menu* _mainMenu;
	Menu* _difficultyMenu;
	Menu* _settingsMenu;
	bool _bIsMenuOpen;
	TextInputBox* _soundCheck;
	TextInputBox* _musicCheck;
	Application() = default;
	~Application();
	sf::RenderWindow* _menuWindow;
	void ShowSettingsCheckBoxes(sf::RenderWindow& window);
	void CreateSettingsCheckBoxes();
	void CreateMenuItems(sf::RenderWindow& window);
	void ToggleCheckbox(TextInputBox* checkBox);
};