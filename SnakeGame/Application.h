#pragma once

class Game;

class Application
{
	Application(const Application& other) = delete;
	Application(Application&& other) noexcept = delete;
	Application& operator=(const Application& other) = delete;
	Application& operator=(Application&& other) = delete;

	static Application& GetInstance();
	const Game* GetGame() const { return _game; }

private:
	Game* _game;
	Application();
	~Application();
};

