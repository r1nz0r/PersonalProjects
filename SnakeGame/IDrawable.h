#pragma once

namespace sf
{
    class RenderWindow;
}

// Interface for objects that can be drawn on an SFML RenderWindow
class IDrawable
{
public:
    // Method to draw the object on the SFML RenderWindow
    virtual void Draw(sf::RenderWindow& window) = 0;
    
    // Virtual destructor for interface cleanup
    virtual ~IDrawable() = default;
};
