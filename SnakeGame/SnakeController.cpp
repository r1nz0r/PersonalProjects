#include "SnakeController.h"
#include "GameSettings.h"
#include "Snake.h"

void SnakeController::SetRotationFromDirection()
{
    const float rotationAngle = static_cast<float>(_movementDirection) * GameSettings::ROTATION_ANGLE;
    _snake.SetHeadRotation(rotationAngle);
}



void SnakeController::SetVelocity()
{
    sf::Vector2u newVelocity = {0, 0};

    switch (GetDirection())
    {
    case EDirection::Up:
        newVelocity.y -= GameSettings::MOVE_DISTANCE;
        break;
    case EDirection::Down:
        newVelocity.y = GameSettings::MOVE_DISTANCE;
        break;
    case EDirection::Left:
        newVelocity.x -= GameSettings::MOVE_DISTANCE;
        break;
    case EDirection::Right:
        newVelocity.x = GameSettings::MOVE_DISTANCE;
        break;
    case EDirection::None:
        newVelocity = sf::Vector2u(0, 0);
        break;
    }
}

void SnakeController::UpdatePosition(const sf::Vector2u& deltaPosition, float deltaTime)
{
    _movementTimer += deltaTime;

    if (_movementTimer < GameSettings::sTimePerCell)
        return;

    _movementTimer = 0.f;
    _snake.SetPosition(_snake.GetPosition() + deltaPosition);
}

void SnakeController::HandleInput(const sf::Keyboard::Scancode& scancode)
{
    switch (scancode)
    {
    case sf::Keyboard::Scancode::W:
        SetDirection(EDirection::Up);
        break;
    case sf::Keyboard::Scancode::S:
        SetDirection(EDirection::Down);
        break;
    case sf::Keyboard::Scancode::A:
        SetDirection(EDirection::Left);
        break;
    case sf::Keyboard::Scancode::D:
        SetDirection(EDirection::Right);
        break;
    default:
        //Остальные клавиши нас не интересуют
        break;
    }
}
