#include "Label.h"

Label::Label(
	const sf::Vector2u& position,
	const sf::Color& color,
	const sf::Font& font,
	const std::string& text,
	const uint32_t textSize
) :
	_textSize(textSize),
	_color(color),
	_font(font)
{
	Initialize(text, position);
}

void Label::Initialize(const std::string& text, const sf::Vector2u& position)
{
	_bIsVisible = true;
	_text.setFont(_font);
	_text.setCharacterSize(_textSize);
	_text.setString(text);
	_text.setPosition(sf::Vector2f(position));
	_text.setFillColor(_color);
}

void Label::Draw(sf::RenderWindow & window)
{
	window.draw(_text);
}
