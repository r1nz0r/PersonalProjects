#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "BaseEntity.h"

namespace sf
{
	class RenderWindow;
}

class Game;

class Snake : public IDrawable
{
public:
	Snake() = default;
	~Snake() override = default;
	void Initialize(const sf::Texture& texture);
	void Draw(sf::RenderWindow& window) override;
	void SetHeadPosition(const sf::Vector2u& position);
	void UpdateBodyPositions();
	void SetHeadRotation(const float rotationAngle);
	const sf::Vector2u& GetHeadPosition() const { return _headPosition; }
	const std::vector<sf::Vector2u>& GetBodyPositions() const { return _bodyPositions; }
	void Grow();
	void Reset();
private:
	sf::Vector2u _headPosition;
	sf::Vector2u _lastHeadPosition;
	std::vector<sf::Vector2u> _bodyPositions;
	sf::Sprite _headSprite;
	sf::Sprite _bodySprite;
};
