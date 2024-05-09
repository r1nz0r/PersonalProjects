#include "Text.h"

Text::Text() : sf::Text() {}

Text::Text(
    const std::string& content,
    const sf::Font& font,
    const sf::Color& color,
    unsigned int characterSize
) : sf::Text(content, font, characterSize)
{
    this->setFillColor(color);
}


void Text::Draw(sf::RenderWindow& window)
{
    window.draw(*this);
}

void Text::Align
(
    const sf::Vector2f& position,
    const Alignment horizontalAlignment,
    const Alignment verticalAlignment
)
{
    sf::Vector2f newPosition {};

    switch (horizontalAlignment)
    {
    case Alignment::Start:
        newPosition.x = position.x - getLocalBounds().width;
        break;
    case Alignment::Center:
        newPosition.x = position.x - getLocalBounds().width / 2;
        break;
    case Alignment::End:
        newPosition.x = position.x;
        break;
    }

    switch (verticalAlignment)
    {
    case Alignment::Start:
        newPosition.y = position.y - getLocalBounds().height;
        break;
    case Alignment::Center:
        newPosition.y = position.y - getLocalBounds().height / 2;
        break;
    case Alignment::End:
        newPosition.y = position.y;
        break;
    }

    setPosition(newPosition);
}

void Text::Align
(
    const sf::FloatRect& container,
    const Alignment horizontalAlignment,
    const Alignment verticalAlignment
)
{
    sf::Vector2f newPosition {};

    switch (horizontalAlignment)
    {
    case Alignment::Start:
        newPosition.x = container.left;
        break;
    case Alignment::Center:
        newPosition.x = container.left + (container.width - getLocalBounds().width) / 2;
        break;
    case Alignment::End:
        newPosition.x = container.left + container.width - getLocalBounds().width;
        break;
    }

    switch (verticalAlignment)
    {
    case Alignment::Start:
        newPosition.y = container.top;
        break;
    case Alignment::Center:
        newPosition.y = container.top + (container.height - getCharacterSize() * 1.2) / 2; // Коэффициент 1.2 получен подбором, на глаз адекватно получается
        break;
    case Alignment::End:
        newPosition.y = container.top + container.height - getLocalBounds().height;
        break;
    }

    setPosition(newPosition);
}