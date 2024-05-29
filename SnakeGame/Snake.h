#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "BaseEntity.h"
#include "Timer.h"
namespace sf
{
	class RenderWindow;
}

enum class EDirection
{
	Up,
	Right,
	Down,
	Left,
	None
};

class Game;

class Snake : public IDrawable
{
public:
	EDirection GetDirection() const { return _movementDirection; }
	Snake() = default;
	~Snake() override = default;
	void Initialize(const sf::Texture& texture);
	void Draw(sf::RenderWindow& window) override;
	void SetHeadPosition(const sf::Vector2u& position);
	void UpdateBodyPositions();
	const sf::Vector2u& GetHeadPosition() const { return _headPosition; }
	const std::vector<sf::Vector2u>& GetBodyPositions() const { return _bodyPositions; }
	void SetDirection(const EDirection newDirection);
	const sf::Vector2u& GetVelocity() const { return _velocity; }
	void SetVelocity();
	void UpdatePosition();
	void SetRotationFromDirection();
	void Grow();
	void Reset();
	void Update();

private:
	sf::Vector2u _headPosition;
	sf::Vector2u _lastHeadPosition;
	std::vector<sf::Vector2u> _bodyPositions;
	sf::Sprite _headSprite;
	sf::Sprite _bodySprite;
	EDirection _movementDirection = EDirection::None;
	Timer _moveTimer;
	sf::Vector2u _velocity { 0, 0 };
	sf::Vector2u DirectionToVelocity(const EDirection direction);
};
