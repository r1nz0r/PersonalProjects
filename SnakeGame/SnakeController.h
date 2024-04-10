#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class Snake;

enum class EDirection
{
	Up,
	Right,
	Down,
	Left,
	None
};

class SnakeController
{
public:
	explicit SnakeController(Snake& snake) : _snake(snake) {}
	~SnakeController() = default;
	void UpdatePosition(const float deltaTime);
	void HandleInput(const sf::Keyboard::Scancode& scancode);
	void Update(const float deltaTime);
	void SetRotationFromDirection();
	EDirection GetDirection() const { return _movementDirection; }
	void SetDirection(const EDirection newDirection) { _movementDirection = newDirection; }
	const sf::Vector2u& GetVelocity() const { return _velocity; }
private:
	void SetVelocity();
	Snake& _snake;
	EDirection _movementDirection = EDirection::None;
	float _movementTimer = 0.0f;
	sf::Vector2u _velocity { 0, 0 };
};
