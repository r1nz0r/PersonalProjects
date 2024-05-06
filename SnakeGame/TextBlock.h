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
    std::vector<Text> _texts; // ������ ���� �������
    sf::Vector2f _start; // ��������� ���������� ���������� �����
    float _verticalSpacing; // ������ ����� ��������
    sf::FloatRect _boundingRect; // ������� ����� ������� (������)
    HorizontalOrigin _hOrigin; // �������������� ������������
    VerticalOrigin _vOrigin; // ������������ ������������

    void UpdateBoundingRect();
    sf::Vector2f GetOriginAdjustment() const;
};
