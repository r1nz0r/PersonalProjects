#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class UIManager;
class IDrawable;

class Graphics
{
public:
    explicit Graphics(sf::RenderWindow& renderWindow);
    void DrawObject(const IDrawable& object) const;
    void Render();
private:
    sf::RenderWindow& _renderWindow;
};
