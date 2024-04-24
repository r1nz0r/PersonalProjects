#pragma once
#include <vector>

#include "Food.h"
#include "IDrawable.h"
#include "Walls.h"

enum class ECellState
{
	Empty,
	SnakeHead,
	SnakeBody,
	Food,
	Walls
};

struct Cell
{
	ECellState state = ECellState::Empty;
};

class GameField : public IDrawable
{
public:
	GameField(Food& food, Wall& wall) : _food(food), _wall(wall) {}
	void Initialize();
	ECellState GetCellState(const uint32_t x, const uint32_t y) const;
	ECellState GetCellState(const sf::Vector2u& position) const;
	bool IsCellFree(const sf::Vector2u& position) const;
	void SetCellState(const uint32_t x, const uint32_t y, const ECellState state);
	void SetCellState(const sf::Vector2u& position, const ECellState state);
	void Clear();
	virtual void Draw(sf::RenderWindow& window) override;
private:
	Food& _food;
	Wall& _wall;
	std::vector<std::vector<Cell>> _cells;
	std::vector<std::vector<Cell>> _emptyCells;

	sf::Vector2u PixelToCell(const sf::Vector2u& pixelPosition) const;
};
