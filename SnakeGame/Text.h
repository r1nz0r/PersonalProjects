#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "IDrawable.h"

// Класс Text, наследуемый от sf::Text
class Text : public sf::Text, public IDrawable
{
public:
    enum class HorizontalAlignment
    {
        Left,
        Center,
        Right
    };

    Text();
    Text(
        const std::string& content,
        const sf::Font& font,
        HorizontalAlignment alignment = HorizontalAlignment::Center,
        const sf::Color& color = sf::Color::White,
        unsigned int characterSize = 30
    );        
    virtual ~Text() = default;

    inline void SetAlignment(HorizontalAlignment alignment);
    inline HorizontalAlignment GetAlignment() const { return _alignment; }
    virtual void Draw(sf::RenderWindow& window) override;
    void AlignHorizontally(const float posX);
    void AlignHorizontally(const sf::FloatRect& container);

private:
    HorizontalAlignment _alignment;
    friend class TextBlock;
};