#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "IDrawable.h"

// Класс Text, наследуемый от sf::Text
class Text : public sf::Text, public IDrawable
{
public:
    enum class Alignment
    {
        Start,
        Center,
        End,
        None
    };

    Text();
    Text(
        const std::string& content,
        const sf::Font& font,
        const sf::Color& color = sf::Color::White,
        unsigned int characterSize = 30
    );        
    virtual ~Text() = default;

    virtual void Draw(sf::RenderWindow& window) override;
    void Align
    (
        const sf::Vector2f& position,
        const Alignment horizontalAlignment = Alignment::Center,
        const Alignment verticalAlignment = Alignment::Center
    );
    void Align
    (
        const sf::FloatRect& container,
        const Alignment horizontalAlignment = Alignment::Center,
        const Alignment verticalAlignment = Alignment::Center
    );

private:
    friend class TextBlock;
};