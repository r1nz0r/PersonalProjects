#include <SFML/Graphics/RenderWindow.hpp>
#include "Snake.h"
#include "GameSettings.h"
#include "SpriteUtils.h"
#include <iostream>

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
	for (size_t i = 0; i < GameSettings::GetGameDifficultySettings().growRate; ++i)
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

	//Так как спрайт у нас один для всех частей тела змейки то его нужно перемещать в цикле на новое место.
	for (const auto& bodyPosition : _bodyPositions)
	{
		_bodySprite.setPosition(sf::Vector2f(bodyPosition.x, bodyPosition.y + GameSettings::UI_HUD_OFFSET_Y));
		window.draw(_bodySprite);
	}
}

void Snake::SetHeadPosition(const sf::Vector2u& position)
{
	//Сохраняем позицию позицию головы до обновления.
	//Это нужно для корректной вставки новой части хвоста при росте змейки.
	_lastHeadPosition = _headPosition;
	_headPosition = position;
	_headSprite.setPosition(sf::Vector2f(_headPosition.x, _headPosition.y + GameSettings::UI_HUD_OFFSET_Y));
}

void Snake::UpdateBodyPositions()
{
	if (_bodyPositions.empty())
		return;

	std::rotate(_bodyPositions.begin(), _bodyPositions.end() - 1, _bodyPositions.end());
	_bodyPositions.front() = _headPosition; // Ставим первый (наиболее удаленный) элемент хвоста на место головы
}

void Snake::Update(const float deltaTime)
{
	SetRotationFromDirection();
	SetVelocity();
	UpdatePosition(deltaTime);
}

sf::Vector2u Snake::DirectionToVelocity(const EDirection direction)
{
	auto velocity = sf::Vector2u(0, 0);

	switch (direction)
	{
	case EDirection::Up:
		velocity.y = -GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::Down:
		velocity.y = GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::Left:
		velocity.x = -GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::Right:
		velocity.x = GameSettings::MOVE_DISTANCE;
		break;
	case EDirection::None:
		break;
	}

	return velocity;
}

void Snake::SetRotationFromDirection()
{
	const float rotationAngle = static_cast<float>(_movementDirection) * GameSettings::ROTATION_ANGLE;
	_headSprite.setRotation(rotationAngle);
}

void Snake::SetDirection(const EDirection newDirection)
{
	EDirection currentDirection = _movementDirection;
	auto velocity = DirectionToVelocity(newDirection);
	auto newHeadPosition = _headPosition + velocity;
		
	// Если хвост змейки не "пуст" и есть коллизия между головой и началом хвоста при новом направлении движения,
	// то выходим из метода не меняя направление.
	if (_bodyPositions.empty() != true && *_bodyPositions.begin() == newHeadPosition)
	{
		return;
	}

	_movementDirection = newDirection;
}

void Snake::SetVelocity()
{
	_velocity = DirectionToVelocity(_movementDirection);
}

void Snake::UpdatePosition(const float deltaTime)
{
	_movementTimer += deltaTime;

	// Проверка достаточно ли времени прошло для перемещения змейки
	if (_movementTimer < GameSettings::sTimePerCell / GameSettings::GetGameDifficultySettings().timeScale)
		return;

	_movementTimer = 0.f;
	UpdateBodyPositions();
	SetHeadPosition(_headPosition + _velocity); // Важно вызывать обновление позиции головы после обновления позиции хвоста.
}