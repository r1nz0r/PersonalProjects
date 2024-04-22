#pragma once

#include <SFML/Graphics.hpp>

void initializeSprite(sf::Sprite& sprite, const sf::Texture& texture,
    const sf::Vector2f& origin, const sf::Vector2f& scale,
    const sf::IntRect& textureRect = sf::IntRect());
