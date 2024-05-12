#include "TextBlock.h"

TextBlock::TextBlock() : TextBlock({}, 10.0f)
{
}

TextBlock::TextBlock(const sf::Vector2f& start, float verticalSpacing, Alignment hOrigin, Alignment vOrigin)
    : _start(start), _verticalSpacing(verticalSpacing), _hOrigin(hOrigin), _vOrigin(vOrigin)
{
    _textAlignment = Text::Alignment::Center;
}

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

const Text& TextBlock::GetText(const int index) const
{
    if (index > 0 && index < _texts.size())
    {
        return _texts[index];
    }
}

void TextBlock::SetColor(const int index, const sf::Color& color)
{
    if (index >= 0 && index < _texts.size())
    {
        _texts[index].setFillColor(color);
    }
}

void TextBlock::AlignTexts()
{
    for (Text& text : _texts)
    {
        text.Align(_boundingRect, _textAlignment, Text::Alignment::None); // Используем метод из класса Text
    }
}

void TextBlock::SetVerticalSpacing(const int spacing)
{
    _verticalSpacing = spacing;
}

void TextBlock::SetStartPosition(const sf::Vector2f position)
{
    _start = position;
}

void TextBlock::SetAlignmentProperties(const Alignment blockHorizontal, const Alignment blockVertical, const Text::Alignment textHorizontal)
{
    _hOrigin = blockHorizontal;
    _vOrigin = blockVertical;
    _textAlignment = textHorizontal;
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
    case Alignment::Start:
        adjustment.x = 0;
        break;
    case Alignment::Center:
        adjustment.x = -_boundingRect.width / 2;
        break;
    case Alignment::End:
        adjustment.x = -_boundingRect.width;
        break;
    }

    switch (_vOrigin)
    {
    case Alignment::Start:
        adjustment.y = 0;
        break;
    case Alignment::Center:
        adjustment.y = -_boundingRect.height / 2;
        break;
    case Alignment::End:
        adjustment.y = -_boundingRect.height;
        break;
    }

    return adjustment;
}