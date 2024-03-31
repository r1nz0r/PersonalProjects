#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "BaseEntity.h"

namespace sf
{
    class RenderWindow;
}

class Game;

class Snake : public IDrawable
{
public:
    Snake() = default;
    ~Snake() override = default;
    void Initialize(const sf::Texture& texture);
    void Draw(sf::RenderWindow& window) const override;
    void SetPosition(const sf::Vector2u& position);
    void SetHeadRotation(const float rotationAngle);
    const sf::Vector2u& GetPosition() const {return _headPosition;}
    void Grow();
private:
    sf::Vector2u _headPosition;
    std::vector<sf::Vector2u> _bodyPositions;
    sf::Sprite _headSprite;
    sf::Sprite _bodySprite;
};
