#include "Text.h"

Text::Text() : sf::Text(), _alignment(HorizontalAlignment::Center) {}

Text::Text(
    const std::string& content,
    const sf::Font& font,
    HorizontalAlignment alignment,
    const sf::Color& color,
    unsigned int characterSize
) : sf::Text(content, font, characterSize), _alignment(alignment)
{
    this->setFillColor(color);
}

inline void Text::SetAlignment(HorizontalAlignment alignment)
{
    _alignment = alignment;
}

void Text::Draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Text::AlignHorizontally(const sf::FloatRect& container)
{
    sf::FloatRect textBounds = getLocalBounds();
    float x = 0;

    switch (_alignment)
    {
    case HorizontalAlignment::Start:
        x = container.left;
        break;
    case HorizontalAlignment::Center:
        x = container.left + (container.width - textBounds.width) / 2;
        break;
    case HorizontalAlignment::End:
        x = container.left + container.width - textBounds.width;
        break;
    }

    setPosition(x, getPosition().y);
}