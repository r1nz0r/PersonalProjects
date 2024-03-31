#pragma once
#include <vector>

enum class CellState
{
    Empty,
    Snake,
    Apple,
    Walls
};

struct Cell
{
    CellState state = CellState::Empty;
};

class GameField
{
public:
    GameField() = default;
    //GameField(const int width,const int height) : _cells(height, std::vector<Cell>(width)) { }
    CellState GetCellState(const int x,const int y) const { return _cells[y][x].state; }
    void SetCellState(const int x,const int y,const CellState state) { _cells[y][x].state = state; }

private:
    std::vector<std::vector<Cell>> _cells;
};
