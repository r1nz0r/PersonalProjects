#include "SpriteUtils.h"

void initializeSprite(sf::Sprite& sprite, const sf::Texture& texture,
	const sf::Vector2f& origin, const sf::Vector2f& scale,
	const sf::IntRect& textureRect)
{
	sprite.setTexture(texture);

	if (!(textureRect.getSize() == sf::Vector2i(0, 0)))
	{
		sprite.setTextureRect(textureRect);
	}

	sprite.setOrigin(origin);
	sprite.setScale(scale);
}
