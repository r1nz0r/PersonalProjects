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
		_inputText.getLocalBounds().width * _lettersMaxCount * 1.25f, // 1.25 - коэффициент расширения для отделения текста от границ по горизонтали
		static_cast<float>(_inputText.getCharacterSize())
	};

	_textInputBorders.setSize(newBordersSize);
}

void TextInputBox::SetBordersVisible(bool bIsVisible)
{
	float borderThickness = bIsVisible ? 2.0f : 0.0f;
	_textInputBorders.setOutlineThickness(borderThickness);
}

void TextInputBox::SetPosition(const sf::Vector2f& position)
{
	_textInputBorders.setPosition(position);
}

void TextInputBox::UpdateText(const std::string& text, const sf::Color& color)
{
	_inputText.setString(text);
	_inputText.setFillColor(color);
	_inputText.Align(_textInputBorders.getGlobalBounds());
}

void TextInputBox::Draw(sf::RenderWindow& window)
{
	window.draw(_textInputBorders);
	window.draw(_inputText);
}

std::string TextInputBox::HandleTextEntered(sf::Event& event)
{
	if (event.text.unicode == '\b')
	{ // Backspace, стирание символа
		if (!_input.empty())
		{
			_bIsInputCorrect = true;
			_input.pop_back();
			UpdateText(_input, _textColor);
		}		
	}
	else if (event.text.unicode > 127)
	{
		_bIsInputCorrect = false;
		ProcessIncorrectInput(); // Некорректный ввод
	}
	else if (event.text.unicode != '\r' && event.text.unicode != '\n')
	{
		if (_input.length() < _lettersMaxCount)
		{ // Добавление символа
			_bIsInputCorrect = true;
			_input += static_cast<char>(event.text.unicode);
			UpdateText(_input, _textColor);
		}
	}

	if (event.text.unicode == '\r' || event.text.unicode == '\n')
	{ // Если нажата клавиша Enter
		std::string textToReturn = _input; // Сохраняем строку во временную переменную
		_input.clear(); // Очищаем исходную строку
		UpdateText("", _textColor);
		return textToReturn;
	}

	if (_bIsInputCorrect)
		SetBordersVisible(true);

	return "";
}

void TextInputBox::ProcessIncorrectInput()
{
	UpdateText(_INCORRECT_INPUT_HINT, _INCORRECT_INPUT_COLOR);
	SetBordersVisible(false);
}