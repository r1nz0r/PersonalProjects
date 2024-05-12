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
	const Game* GetGame() const { return _game; }

private:
	Game* _game;
	Menu* _menu;
	TextInputBox* _soundCheck;
	TextInputBox* _musicCheck;
	Application() = default;
	~Application();
	void ShowSettingsCheckBoxes(sf::RenderWindow& window);
	void CreateSettingsCheckBoxes();
	void ToggleCheckbox(TextInputBox* checkBox);
};