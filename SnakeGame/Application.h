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
	Game* GetGame() const { return _game; }

private:
	Game* _game;
	Application() = default;
	~Application();
};