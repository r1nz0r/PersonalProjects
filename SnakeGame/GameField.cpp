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
	SetCellState(position.x, position.y, state);
}

ECellState GameField::GetCellState(const uint32_t x, const uint32_t y) const
{
	if (y >= _cells.size() || x >= _cells[y].size())
		return ECellState::Walls;

	return _cells[y][x].state;
}

ECellState GameField::GetCellState(const sf::Vector2u& position) const
{
	return GetCellState(position.x, position.y);
}

void GameField::Print() const
{
	system("cls");

	for (size_t y = 0; y < GameSettings::sCellCountY; ++y)
	{
		for (size_t x = 0; x < GameSettings::sCellCountX; ++x)
		{
			const ECellState state = GetCellState(x, y);
			char symbol;

			switch (state)
			{
			case ECellState::SnakeHead:
				symbol = '@';
				break;
			case ECellState::SnakeBody:
				symbol = 'B';
				break;
			case ECellState::Food:
				symbol = 'F';
				break;
			case ECellState::Walls:
				symbol = 'W';
				break;
			case ECellState::Empty:
			default:
				symbol = '.';
				break;
			}

			std::cout << symbol << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
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
				_wall.SetPosition(sf::Vector2u(x * cellSize, y * cellSize + GameSettings::UI_HUD_OFFSET_Y));
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
