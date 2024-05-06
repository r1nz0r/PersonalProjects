#pragma once
#include "Text.h"

class TextBlock
{
public:

    enum class HorizontalOrigin
    {
        Left,
        Center,
        Right
    };

    enum class VerticalOrigin
    {
        Top,
        Center,
        Bottom
    };

    TextBlock(
        const sf::Vector2f& start,
        float verticalSpacing,
        HorizontalOrigin hOrigin = HorizontalOrigin::Center,
        VerticalOrigin vOrigin = VerticalOrigin::Center
    );

    void AddText(Text& text);
    void AddText(
        const std::string& content,
        const sf::Font& font,
        Text::HorizontalAlignment alignment = Text::HorizontalAlignment::Center,
        const sf::Color& color = sf::Color::White,
        unsigned int characterSize = 30
    );
    void AlignTexts();
    void Draw(sf::RenderWindow& window) const;
    void Clear();

private:
    std::vector<Text> _texts; // Список всех текстов
    sf::Vector2f _start; // Начальная координата текстового блока
    float _verticalSpacing; // Отступ между текстами
    sf::FloatRect _boundingRect; // Границы блока текстов (размер)
    HorizontalOrigin _hOrigin; // Горизонтальное выравнивание
    VerticalOrigin _vOrigin; // Вертикальное выравнивание

    void UpdateBoundingRect();
    sf::Vector2f GetOriginAdjustment() const;
};
