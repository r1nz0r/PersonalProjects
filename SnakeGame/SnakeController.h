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
    explicit SnakeController(Snake& snake) : _snake(snake){}
    ~SnakeController() = default;
    void UpdatePosition(const sf::Vector2u& deltaPosition, float deltaTime);
    void HandleInput(const sf::Keyboard::Scancode& scancode);
    void Update(float deltaTime);
    void SetRotationFromDirection();
    EDirection GetDirection() const { return _movementDirection; }
    void SetDirection(const EDirection newDirection) { _movementDirection = newDirection; }
    const sf::Vector2f& GetVelocity() const { return _velocity; }
private:
    void SetVelocity();    
    Snake& _snake;
    EDirection _movementDirection = EDirection::None;
    float _movementTimer = 0.0f;
    sf::Vector2f _velocity{0.f, 0.f};
};
