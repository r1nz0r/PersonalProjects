#include "BaseEntity.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameSettings.h"

void BaseEntity::Initialize(const sf::Texture& texture, const sf::Vector2i& tilePosition)
{
	_sprite.setTexture(texture);
	_sprite.setTextureRect(
		sf::IntRect(
			tilePosition.x,
			tilePosition.y,
			GameSettings::TILE_SIZE.x,
			GameSettings::TILE_SIZE.y)
	);
	_sprite.setScale(GameSettings::TILE_SCALE);
	_sprite.setPosition(sf::Vector2f(0.f, 0.f));
}

void BaseEntity::SetTilePosition(const sf::Vector2i tilePosition)
{
	_sprite.setTextureRect(
		sf::IntRect(
			tilePosition.x,
			tilePosition.y,
			GameSettings::TILE_SIZE.x,
			GameSettings::TILE_SIZE.y)
	);
}

void BaseEntity::SetPosition(const sf::Vector2u& position)
{
	_position = position;
	_sprite.setPosition(sf::Vector2f(position.x, position.y + GameSettings::UI_HUD_OFFSET_Y));
}

const sf::Vector2u& BaseEntity::GetPosition() const
{
	return _position;
}

void BaseEntity::Draw(sf::RenderWindow& window)
{
	window.draw(_sprite);
}
