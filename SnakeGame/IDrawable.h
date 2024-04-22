#pragma once

namespace sf
{
	class RenderWindow;
}

class IDrawable
{
public:
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual ~IDrawable() = default;
};
