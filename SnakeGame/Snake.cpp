#include "Snake.h"
#include "GameSettings.h"
#include <SFML/Graphics/RenderWindow.hpp>

void Snake::Initialize(const sf::Texture& texture)
{
    _headSprite.setTexture(texture);
    _headSprite.setTextureRect(sf::IntRect(8, 24, GameSettings::TILE_SIZE.x, GameSettings::TILE_SIZE.y));
    _headSprite.setOrigin(GameSettings::TILE_SIZE.x / 2.f, GameSettings::TILE_SIZE.y / 2.f);
    _headSprite.setScale(GameSettings::TILE_SCALE);
    _headSprite.setPosition(sf::Vector2f(320.f, 320.f));

    _bodySprite.setTexture(texture);
    _bodySprite.setTextureRect(sf::IntRect(40, 24, GameSettings::TILE_SIZE.x, GameSettings::TILE_SIZE.y));
    _bodySprite.setOrigin(GameSettings::TILE_SIZE.x / 2.f, GameSettings::TILE_SIZE.y / 2.f);
    _bodySprite.setScale(GameSettings::TILE_SCALE);
    _bodySprite.setPosition(sf::Vector2f(320.f, 352.f));
}

void Snake::Grow()
{
}

void Snake::Draw(sf::RenderWindow& window) const
{
    window.draw(_headSprite);
    window.draw(_bodySprite);
}

void Snake::SetPosition(const sf::Vector2u& position)
{
}

void Snake::SetHeadRotation(const float rotationAngle)
{
    _headSprite.setRotation(rotationAngle);
}
