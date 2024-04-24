#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "IDrawable.h"

class Label : public IDrawable
{
public:
	Label(
		const sf::Vector2u& position,
		const sf::Color& color,
		const sf::Font& font,
		const std::string& text = "",
		const uint32_t textSize = 30
	);

	~Label() = default;

	inline bool IsVisible() const { return _bIsVisible; }
	void SetVisibility(bool bIsVisible) { _bIsVisible = bIsVisible; }
	inline sf::Vector2u GetPosition() const { return sf::Vector2u(_text.getPosition()); }
	void SetPosition(const sf::Vector2u& position) { _text.setPosition(sf::Vector2f(position)); }
	void SetText(const std::string& text) { _text.setString(text); }
	float GetLabelWidth() const { return _text.getLocalBounds().width; }
	float GetLabelHeight() const { return _text.getLocalBounds().height; }
	virtual void Draw(sf::RenderWindow& window);

private:
	void Initialize(const std::string& text, const sf::Vector2u& position);
	bool _bIsVisible;
	sf::Font _font;
	sf::Text _text;
	sf::Color _color;
	uint32_t _textSize = 30;
};