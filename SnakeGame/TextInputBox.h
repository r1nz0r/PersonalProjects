#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "IDrawable.h"
#include "Text.h"

/**
 * @class TextInputBox
 * @brief ����� ��� ���������� ���������� ���� ����� � ������������ �� ���������� ��������.
 *
 * ���� ����� ��������� ���������� ��������� ���� �����, �������� ������������ ���������� ��������,
 * ������������� ����� ������, ����� � ����. �� ����� ������������ ������� ����� ������ � �������
 * ��������� ��� ������� ������� Enter.
 */
class TextInputBox : public IDrawable
{
public:
	/**
	* @brief ����������� ������ TextInputBox.
	* @param font �����, ������������ ��� ����������� ������.
	* @param lettersMaxCount ������������ ���������� ��������, ����������� � ���� �����.
	* @param textColor ���� ������.
	* @param outLineColor ���� ����� ������ ���� �����.
	* @param fillColor ���� ���� ���� �����.
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
	* @brief ������������� ������������� ����� ������� (origin) � �����.
	* @param x �������������� �������� ������������ ������ (0.0 - 1.0).
	* @param y ������������ �������� ������������ ������ (0.0 - 1.0).
	*/
	void SetRelativeOrigin(const float x, const float y);

	/**
	* @brief ������������� ��������� ����� ������ ���� �����.
	* @param bIsVisible ���������, ������ �� ����� ���� �������.
	*/
	void SetBordersVisible(bool bIsVisible);

	/**
	* @brief ������������� ������� ���� �����.
	* @param position ����� ������� ���� �����.
	*/
	void SetPosition(const sf::Vector2f& position);

	/**
	* @brief ��������� ����� � ���� �����.
	* @param text ����� �����.
	* @param color ���� ������.
	*/
	void UpdateText(const std::string& text, const sf::Color& color);

	/**
	* @brief ���������� ������� ����� �� ���� �����.
	* @return ������� �����.
	*/
	std::string GetText() const;

	/**
	* @brief ������ ���� ����� � ����� ������ ����.
	* @param window ����, � ������� ���������� ���������.
	*/
	virtual void Draw(sf::RenderWindow& window) override;

	/**
	* @brief ������������ ��������� ����� �� ������� � ���������� ���������.
	* @param event ������� �����.
	* @return ���������� ��������� �����, ���� ������ ������� Enter, ����� ���������� ������ ������.
	*/
	std::string HandleTextEntered(sf::Event& event);
private:
	sf::RectangleShape _textInputBorders; // ����� ������ ���� �����.
	std::string _input; // ������� ��������� �����.
	Text _inputText; // ������ ��� ����������� ������.
	sf::Color _textColor; // ���� ������.
	uint32_t _lettersMaxCount; // ������������ ���������� �������� � ���� �����.
	bool _bIsInputCorrect; // ��������� ��������� �� ������� ����.

	static constexpr float _BORDER_THICKNESS = 2.0f;  // ������� �����.
	static constexpr float _BORDER_EXPANSION_COEFFICIENT = 1.25f;  // ����������� ���������� ����� ��� ��������� ������ �� ������ �� �����������
	static constexpr char _BACKSPACE = '\b';  // ������� Backspace.
	static constexpr char _ENTER = '\r';  // ������� Enter.
	static constexpr char _NEW_LINE = '\n';  // ������� ����� ������.
	static constexpr const char* _INCORRECT_INPUT_HINT = "Please, type only numbers or a-Z letters.";  // ��������� ��� ������������ �����.
	inline static const const sf::Color _INCORRECT_INPUT_COLOR = sf::Color::Red;  // ���� ������ ��� ������������ �����.

	void Initialize(const sf::Color& outLineColor, const sf::Color& fillColor);

	/**
	* @brief ������������ ������������ ����, ��������� ��������� �� ������ � ������� �����.
	*/
	void ProcessIncorrectInput();

	/**
	* @brief ������� ��������� ������ �� ������.
	*/
	void RemoveLastCharacter();

	/**
	* @brief ������������ ������� ������� Enter.
	* @return ��������� ����� �� ������� ������� Enter.
	*/
	const std::string OnEnterPressed();

	/**
	* @brief ��������� ������ ����� ������ ���� ����� �� ������ ���������� ��������.
	*/
	void UpdateBordersRectSize();
};