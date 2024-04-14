#include <SFML/Graphics/RenderWindow.hpp>
#include "Snake.h"
#include "GameSettings.h"
#include "SpriteUtils.h"

void Snake::Initialize(const sf::Texture& texture)
{
	_headPosition = GameSettings::SNAKE_START_POSITION;

	sf::Vector2f tileSize(sf::Vector2f(GameSettings::TILE_SIZE.x, GameSettings::TILE_SIZE.y));
	sf::Vector2f tileOrigin(tileSize.x / 2.f, tileSize.y / 2.f);
	sf::Vector2f tileScale(GameSettings::TILE_SCALE);

	initializeSprite(_headSprite, texture, tileOrigin, tileScale, sf::IntRect(8, 24, tileSize.x, tileSize.y));
	initializeSprite(_bodySprite, texture, tileOrigin, tileScale, sf::IntRect(40, 24, tileSize.x, tileSize.y));

	_headSprite.setPosition(sf::Vector2f(_headPosition));
}

void Snake::Grow()
{
	_bodyPositions.push_back(_lastHeadPosition);
}

void Snake::Reset()
{
	_headPosition = GameSettings::SNAKE_START_POSITION;
	_bodyPositions.clear();
}

void Snake::Draw(sf::RenderWindow& window)
{
	window.draw(_headSprite);

	for (const auto& bodyPosition : _bodyPositions)
	{
		_bodySprite.setPosition(sf::Vector2f(bodyPosition));
		window.draw(_bodySprite);
	}
}

void Snake::SetHeadPosition(const sf::Vector2u& position)
{
	_lastHeadPosition = _headPosition;
	_headPosition = position;
	_headSprite.setPosition(sf::Vector2f(_headPosition));
}

void Snake::UpdateBodyPositions()
{
	if (_bodyPositions.empty())
		return;

	std::rotate(_bodyPositions.begin(), _bodyPositions.end() - 1, _bodyPositions.end());
	_bodyPositions.front() = _headPosition;  // Update head position after rotation
}

void Snake::Update(const float deltaTime)
{
	SetRotationFromDirection();
	SetVelocity();
	UpdatePosition(deltaTime);
}

void Snake::SetRotationFromDirection()
{
	const float rotationAngle = static_cast<float>(_movementDirection) * GameSettings::ROTATION_ANGLE;
	_headSprite.setRotation(rotationAngle);
}

void Snake::SetDirection(const EDirection newDirection)
{
	EDirection currentDirection = GetDirection();
	
	//Проверка на то что перемещение меняется не на обратное текущему.
	if (std::abs(static_cast<int>(currentDirection) - static_cast<int>(newDirection)) != OPPOSITE_DIRECTION_DIFF)
	{
		_movementDirection = newDirection;
	}
}

void Snake::SetVelocity()
{
	_velocity = sf::Vector2u(0, 0);

	switch (GetDirection())
	{
	case EDirection::Up:
		_velocity.y = -GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::Down:
		_velocity.y = GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::Left:
		_velocity.x = -GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::Right:
		_velocity.x = GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::None:
		break;
	}
}

void Snake::UpdatePosition(const float deltaTime)
{
	_movementTimer += deltaTime;

	// Check if enough time has passed for movement
	if (_movementTimer < GameSettings::sTimePerCell)
		return;

	_movementTimer = 0.f;
	UpdateBodyPositions();
	SetHeadPosition(GetHeadPosition() + _velocity);
	//auto bodyPositions = _snake.GetBodyPositions();
}