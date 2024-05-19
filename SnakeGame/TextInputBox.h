#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "IDrawable.h"
#include "Text.h"

/**
 * @class TextInputBox
 * @brief Класс для реализации текстового поля ввода с ограничением на количество символов.
 *
 * Этот класс позволяет отображать текстовое поле ввода, задавать максимальное количество символов,
 * устанавливать цвета текста, рамки и фона. Он также обрабатывает события ввода текста и выводит
 * результат при нажатии клавиши Enter.
 */
class TextInputBox : public IDrawable
{
public:
	/**
	* @brief Конструктор класса TextInputBox.
	* @param font Шрифт, используемый для отображения текста.
	* @param lettersMaxCount Максимальное количество символов, разрешенных в поле ввода.
	* @param textColor Цвет текста.
	* @param outLineColor Цвет рамки вокруг поля ввода.
	* @param fillColor Цвет фона поля ввода.
	*/
	TextInputBox(
		const sf::Font& font,
		const uint32_t lettersMaxCount = 12,
		const sf::Color& textColor = sf::Color::White,
		const sf::Color& outLineColor = sf::Color::White,
		const sf::Color& fillColor = sf::Color::Black
	);
	virtual ~TextInputBox() = default;

	/**
	* @brief Устанавливает относительную точку отсчета (origin) в рамке.
	* @param x Горизонтальное смещение относительно границ (0.0 - 1.0).
	* @param y Вертикальное смещение относительно границ (0.0 - 1.0).
	*/
	void SetRelativeOrigin(const float x, const float y);

	/**
	* @brief Устанавливает видимость рамки вокруг поля ввода.
	* @param bIsVisible Указывает, должна ли рамка быть видимой.
	*/
	void SetBordersVisible(bool bIsVisible);

	/**
	* @brief Устанавливает позицию поля ввода.
	* @param position Новая позиция поля ввода.
	*/
	void SetPosition(const sf::Vector2f& position);

	/**
	* @brief Обновляет текст в поле ввода.
	* @param text Новый текст.
	* @param color Цвет текста.
	*/
	void UpdateText(const std::string& text, const sf::Color& color);

	/**
	* @brief Возвращает текущий текст из поля ввода.
	* @return Текущий текст.
	*/
	std::string GetText() const;

	/**
	* @brief Рисует поле ввода и текст внутри него.
	* @param window Окно, в котором происходит отрисовка.
	*/
	virtual void Draw(sf::RenderWindow& window) override;

	/**
	* @brief Обрабатывает введенный текст из события и возвращает результат.
	* @param event Событие ввода.
	* @return Возвращает введенный текст, если нажата клавиша Enter, иначе возвращает пустую строку.
	*/
	std::string HandleTextEntered(const sf::Event& event);
private:
	sf::RectangleShape _textInputBorders; // Рамка вокруг поля ввода.
	std::string _input; // Текущий введенный текст.
	Text _inputText; // Объект для отображения текста.
	sf::Color _textColor; // Цвет текста.
	uint32_t _lettersMaxCount; // Максимальное количество символов в поле ввода.
	bool _bIsInputCorrect; // Указывает корректен ли текущий ввод.

	static constexpr float _BORDER_THICKNESS = 2.0f;  // Толщина рамки.
	static constexpr float _BORDER_EXPANSION_COEFFICIENT = 1.25f;  // Коэффициент расширения рамки для отделения текста от границ по горизонтали
	static constexpr char _BACKSPACE = '\b';  // Клавиша Backspace.
	static constexpr char _ENTER = '\r';  // Клавиша Enter.
	static constexpr char _NEW_LINE = '\n';  // Клавиша новой строки.
	static constexpr const char* _INCORRECT_INPUT_HINT = "Please, type only numbers or a-Z letters.";  // Подсказка при некорректном вводе.
	inline static const const sf::Color _INCORRECT_INPUT_COLOR = sf::Color::Red;  // Цвет текста при некорректном вводе.

	void Initialize(const sf::Color& outLineColor, const sf::Color& fillColor);

	/**
	* @brief Обрабатывает некорректный ввод, показывая сообщение об ошибке и скрывая рамку.
	*/
	void ProcessIncorrectInput();

	/**
	* @brief Удаляет последний символ из текста.
	*/
	void RemoveLastCharacter();

	/**
	* @brief Обрабатывает нажатие клавиши Enter.
	* @return Введенный текст до нажатия клавиши Enter.
	*/
	const std::string OnEnterPressed();

	/**
	* @brief Обновляет размер рамки вокруг поля ввода на основе количества символов.
	*/
	void UpdateBordersRectSize();
};