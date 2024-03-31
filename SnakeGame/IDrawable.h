#pragma once

namespace sf
{
    class RenderWindow;
}

class IDrawable
{
    public:
        virtual void Draw(sf::RenderWindow& window) const = 0;
        virtual ~IDrawable() = default;
};
