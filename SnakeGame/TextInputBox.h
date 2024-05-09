#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "IDrawable.h"
#include "Text.h"

class TextInputBox : public IDrawable
{
public:
	TextInputBox(
		const sf::Font& font,
		const uint32_t lettersMaxCount = 12,
		const sf::Color& textColor = sf::Color::White,
		const sf::Color& outLineColor = sf::Color::White,
		const sf::Color& fillColor = sf::Color::Black
	);
	virtual ~TextInputBox() = default;
	// Устанавливаем Pivot в относительных коээфициентах от 0 до 1.0.
	void SetRelativeOrigin(const float x, const float y);
	// Обновляем размеры рамки в соответствии с допустимым текстом внутри
	void UpdateBordersRectSize();
	void SetBordersVisible(bool bIsVisible);
	void SetPosition(const sf::Vector2f& position);
	void UpdateText(const std::string& text, const sf::Color& color);
	virtual void Draw(sf::RenderWindow& window) override;
	std::string HandleTextEntered(sf::Event& event);

private:
	sf::RectangleShape _textInputBorders;
	std::string _input;
	Text _inputText;
	const std::string _INCORRECT_INPUT_HINT = "Please, type only numbers or a-Z letters.";
	const sf::Color _INCORRECT_INPUT_COLOR = sf::Color::Magenta;
	sf::Color _textColor;
	//sf::Color _outLineColor;
	//sf::Color _fillColor;
	uint32_t _lettersMaxCount;
	bool _bIsInputCorrect;

	void Initialize(const sf::Color& outLineColor, const sf::Color& fillColor);
	void ProcessIncorrectInput();
};