#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "IDrawable.h"

// Base class for entities in the game.
class BaseEntity : public IDrawable
{
public:
	BaseEntity() = default;
	virtual ~BaseEntity() = default;

	virtual void Initialize(const sf::Texture& texture, const sf::Vector2i& tilePosition);
	virtual void SetTilePosition(const sf::Vector2i tilePosition);
	virtual void SetPosition(const sf::Vector2u& position);
	virtual const sf::Vector2u& GetPosition() const;
	virtual void Draw(sf::RenderWindow& window) override;

protected:
	sf::Vector2u _position;
	sf::Sprite _sprite;
};
