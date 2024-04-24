#include <iostream>
#include <stdexcept>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameField.h"
#include "GameSettings.h"


void GameField::Initialize()
{
	_cells.resize(GameSettings::sCellCountY);

	for (size_t y = 0; y < GameSettings::sCellCountY; ++y)
	{
		_cells[y].resize(GameSettings::sCellCountX);
	}

	Clear();
}

void GameField::Clear()
{
	for (size_t y = 0; y < GameSettings::sCellCountY; ++y)
	{
		for (size_t x = 0; x < GameSettings::sCellCountX; ++x)
		{
			if (x == 0 || y == 0 || x == GameSettings::sCellCountX - 1 || y == GameSettings::sCellCountY - 1)
				_cells[y][x].state = ECellState::Walls;
			else
				_cells[y][x].state = ECellState::Empty;
		}
	}
}

void GameField::SetCellState(const uint32_t x, const uint32_t y, const ECellState state)
{
	if (y < _cells.size() && x < _cells[y].size())
		_cells[y][x].state = state;
	else
		throw std::out_of_range("Warning: Trying to set cell state out of bounds.");
}

void GameField::SetCellState(const sf::Vector2u& position, const ECellState state)
{
	auto positionInCell = PixelToCell(position);
	SetCellState(positionInCell.x, positionInCell.y, state);
}

ECellState GameField::GetCellState(const uint32_t x, const uint32_t y) const
{
	if (y >= _cells.size() || x >= _cells[y].size())
		return ECellState::Walls;

	return _cells[y][x].state;
}

ECellState GameField::GetCellState(const sf::Vector2u& position) const
{
	auto positionInCell = PixelToCell(position);
	return GetCellState(positionInCell.x, positionInCell.y);
}

bool GameField::IsCellFree(const sf::Vector2u& position) const
{
	auto cellState = GetCellState(position);

	if (cellState == ECellState::Empty)
		return true;

	return false;
}

sf::Vector2u GameField::PixelToCell(const sf::Vector2u& pixelPosition) const
{
	int cellX = pixelPosition.x / GameSettings::CELL_SIZE;
	int cellY = pixelPosition.y / GameSettings::CELL_SIZE;
	return sf::Vector2u(cellX, cellY);
}

void GameField::Draw(sf::RenderWindow& window)
{
	const float cellSize = static_cast<float>(GameSettings::CELL_SIZE);
	const sf::Color wallColor = sf::Color::Red;
	const sf::Color groundColor = sf::Color::Black;

	for (size_t y = 0; y < GameSettings::sCellCountY; ++y)
	{
		for (size_t x = 0; x < GameSettings::sCellCountX; ++x)
		{
			sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
			cellShape.setPosition(x * cellSize, y * cellSize + GameSettings::UI_HUD_OFFSET_Y);

			ECellState state = GetCellState(x, y);

			switch (state)
			{
			case ECellState::Walls:
				_wall.SetPosition(sf::Vector2u(x * cellSize, y * cellSize));
				_wall.Draw(window);
				break;
			default:
				cellShape.setFillColor(groundColor);
				window.draw(cellShape);
				break;
			}
		}
	}
}