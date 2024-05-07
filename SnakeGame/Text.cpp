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

void Text::AlignHorizontally(const float posX)
{
    float x = 0;

    switch (_alignment)
    {
    case HorizontalAlignment::Left:
        x = posX - getLocalBounds().width;
        break;
    case HorizontalAlignment::Center:
        x = posX - getLocalBounds().width / 2;
        break;
    case HorizontalAlignment::Right:
        x = posX;
        break;
    }

    setPosition(x, getPosition().y);
}

void Text::AlignHorizontally(const sf::FloatRect& container)
{
    float x = 0;

    switch (_alignment)
    {
    case HorizontalAlignment::Left:
        x = container.left;
        break;
    case HorizontalAlignment::Center:
        x = container.left + (container.width - getLocalBounds().width) / 2;
        break;
    case HorizontalAlignment::Right:
        x = container.left + container.width - getLocalBounds().width;
        break;
    }

    setPosition(x, getPosition().y);
}