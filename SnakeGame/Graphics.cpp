#include "Graphics.h"
#include "IDrawable.h"


Graphics::Graphics(sf::RenderWindow& renderWindow) :
    _renderWindow(renderWindow)
{}

void Graphics::DrawObject(const IDrawable& object) const
{
    object.Draw(_renderWindow);
}
