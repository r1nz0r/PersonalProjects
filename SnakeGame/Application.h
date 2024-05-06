#pragma once

class Game;
class Menu;

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
	Application() = default;
	~Application();
};