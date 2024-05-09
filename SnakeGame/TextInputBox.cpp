#include "TextInputBox.h"

TextInputBox::TextInputBox(
	const sf::Font& font,
	const uint32_t lettersMaxCount,
	const sf::Color& textColor,
	const sf::Color& outLineColor,
	const sf::Color& fillColor
) : _lettersMaxCount(lettersMaxCount),
_textColor(textColor),
_input(),
_inputText("A", font), // Иницализация буквой для корректного расчета габаритов контура.
_textInputBorders()
{
	Initialize(outLineColor, fillColor);
}

void TextInputBox::Initialize(const sf::Color& outLineColor, const sf::Color& fillColor)
{
	_bIsInputCorrect = true;
	UpdateBordersRectSize();
	_textInputBorders.setOutlineColor(outLineColor);
	_textInputBorders.setFillColor(fillColor);
	SetBordersVisible(true);
	_inputText.setString(""); // Сбрасываем текст внутри после инициализации рамки.
	_inputText.Align(_textInputBorders.getGlobalBounds());
}

void TextInputBox::SetRelativeOrigin(const float x, const float y)
{
	if (x < .0 || y < .0 || x > 1.0 || y > 1.0)
		return;

	float left = (_textInputBorders.getLocalBounds().left + _textInputBorders.getLocalBounds().width) * x;
	float top = (_textInputBorders.getLocalBounds().top + _textInputBorders.getLocalBounds().height) * y;
	_textInputBorders.setOrigin(left, top);
}

void TextInputBox::UpdateBordersRectSize()
{
	sf::Vector2f newBordersSize
	{
		_inputText.getLocalBounds().width * _lettersMaxCount * _BORDER_EXPANSION_COEFFICIENT,
		static_cast<float>(_inputText.getCharacterSize())
	};

	_textInputBorders.setSize(newBordersSize);
}

void TextInputBox::SetBordersVisible(bool bIsVisible)
{
	float borderThickness = bIsVisible ? _BORDER_THICKNESS : 0.0f;
	_textInputBorders.setOutlineThickness(borderThickness);
}

void TextInputBox::SetPosition(const sf::Vector2f& position)
{
	_textInputBorders.setPosition(position);
}

void TextInputBox::UpdateText(const std::string& text, const sf::Color& color)
{
	if (_inputText.getString() == text)
		return;

	_inputText.setString(text);
	_inputText.setFillColor(color);
	_inputText.Align(_textInputBorders.getGlobalBounds());
}

std::string TextInputBox::GetText() const
{
	return _inputText.getString();
}

void TextInputBox::Draw(sf::RenderWindow& window)
{
	window.draw(_textInputBorders);
	window.draw(_inputText);
}

std::string TextInputBox::HandleTextEntered(sf::Event& event)
{
	char character = static_cast<char>(event.text.unicode);

	if (character == _BACKSPACE)
	{		
		RemoveLastCharacter();
	}
	else if (event.text.unicode > 127)
	{
		_bIsInputCorrect = false;
		ProcessIncorrectInput();
	}
	else if (character == _ENTER || character == _NEW_LINE)
	{
		return OnEnterPressed();
	}
	else if (_input.length() < _lettersMaxCount)
	{
		_bIsInputCorrect = true;
		_input += character;
		UpdateText(_input, _textColor);
	}

	if (_bIsInputCorrect)
		SetBordersVisible(true);

	return "";
}

const std::string TextInputBox::OnEnterPressed()
{
	if (!_bIsInputCorrect)
		SetBordersVisible(true);

	std::string textToReturn = _input; // Сохраняем строку во временную переменную
	_input.clear(); // Очищаем исходную строку
	UpdateText("", _textColor);
	return textToReturn;
}

void TextInputBox::RemoveLastCharacter()
{
	if (!_input.empty())
	{
		_bIsInputCorrect = true;
		_input.pop_back();
		UpdateText(_input, _textColor);
	}
}

void TextInputBox::ProcessIncorrectInput()
{
	UpdateText(_INCORRECT_INPUT_HINT, _INCORRECT_INPUT_COLOR);
	SetBordersVisible(false);
}