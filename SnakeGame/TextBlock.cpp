#include "TextBlock.h"

TextBlock::TextBlock(const sf::Vector2f& start, float verticalSpacing, HorizontalOrigin hOrigin, VerticalOrigin vOrigin)
    : _start(start), _verticalSpacing(verticalSpacing), _hOrigin(hOrigin), _vOrigin(vOrigin)
{}

void TextBlock::AddText(Text& text)
{
    if (_texts.empty())
    {
        text.setPosition(_start);
    }
    else
    {
        const Text& lastText = _texts.back();
        sf::FloatRect lastBounds = lastText.getGlobalBounds();
        text.setPosition(lastBounds.left, lastBounds.top + lastBounds.height + _verticalSpacing);
    }

    _texts.push_back(text);
    UpdateBoundingRect();
}

void TextBlock::AddText(const std::string& content, const sf::Font& font, const sf::Color& color, unsigned int characterSize)
{
    {
        Text newText(content, font, color, characterSize);
        AddText(newText);
    }
}

void TextBlock::AlignTexts()
{
    for (Text& text : _texts)
    {
        text.Align(_boundingRect); // Используем метод из класса Text
    }
}

void TextBlock::Draw(sf::RenderWindow& window) const
{
    sf::Vector2f adjustment = GetOriginAdjustment(); // Смещение текста в соответствии с Origin-ом блока

    for (const Text& text : _texts)
    {
        sf::Text adjustedText = text;
        adjustedText.setPosition(text.getPosition() + adjustment);
        window.draw(adjustedText);
    }
}

void TextBlock::Clear()
{
    _texts.clear();
}

void TextBlock::UpdateBoundingRect()
{
    if (_texts.empty())
    {
        _boundingRect = sf::FloatRect(_start.x, _start.y, 0, 0);
        return;
    }

    // Инициализация границ первымым текстом
    _boundingRect = _texts.front().getGlobalBounds();

    // Обновление границ, чтобы охватить все тексты
    for (const Text& text : _texts)
    {
        const sf::FloatRect textBounds = text.getGlobalBounds();

        // Обновляем левую и верхнюю границы
        _boundingRect.left = std::min(_boundingRect.left, textBounds.left);
        _boundingRect.top = std::min(_boundingRect.top, textBounds.top);

        // Определение правой и нижней границ
        const float right = textBounds.left + textBounds.width;
        const float bottom = textBounds.top + textBounds.height;

        // Обновление ширины и высоты
        _boundingRect.width = std::max(_boundingRect.width, right - _boundingRect.left);
        _boundingRect.height = std::max(_boundingRect.height, bottom - _boundingRect.top);
    }
}

sf::Vector2f TextBlock::GetOriginAdjustment() const
{
    sf::Vector2f adjustment { 0, 0 };

    switch (_hOrigin)
    {
    case HorizontalOrigin::Left:
        adjustment.x = 0;
        break;
    case HorizontalOrigin::Center:
        adjustment.x = -_boundingRect.width / 2;
        break;
    case HorizontalOrigin::Right:
        adjustment.x = -_boundingRect.width;
        break;
    }

    switch (_vOrigin)
    {
    case VerticalOrigin::Top:
        adjustment.y = 0;
        break;
    case VerticalOrigin::Center:
        adjustment.y = -_boundingRect.height / 2;
        break;
    case VerticalOrigin::Bottom:
        adjustment.y = -_boundingRect.height;
        break;
    }

    return adjustment;
}