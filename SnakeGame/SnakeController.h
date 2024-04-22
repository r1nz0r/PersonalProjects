#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class Snake;

class SnakeController
{
public:
	explicit SnakeController(Snake& snake) : _snake(snake) {}
	~SnakeController() = default;
	void HandleInput(const sf::Keyboard::Scancode& scancode);
private:
	Snake& _snake;
};
