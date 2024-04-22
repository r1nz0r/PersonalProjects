#pragma once
#include <SFML/System.hpp>

class GameSettings
{
public:
	// Настройки игрового поля
	inline static const sf::Vector2f TILE_SCALE { 4.0f, 4.0f };
	inline static const sf::Vector2i TILE_SIZE { 8, 8 };
	inline static uint32_t sCellCountX = 20;
	inline static uint32_t sCellCountY = 20;
	inline static const int CELL_SIZE = TILE_SIZE.x * static_cast<int>(TILE_SCALE.x);

	// Настройки змейки
	static constexpr int ROTATION_ANGLE = 90;
	inline static const int MOVE_DISTANCE = CELL_SIZE;
	inline static float sTimePerCell = 0.15f; // Сколько времени необходимо для перемещения змейки на 1 ячейку [с].
	inline static const sf::Vector2u SNAKE_START_POSITION
	{
		sCellCountX / 2 * CELL_SIZE - CELL_SIZE / 2,
		sCellCountX / 2 * CELL_SIZE - CELL_SIZE / 2
	};

	// Настройки окна
	inline static const std::string GAME_TITLE = "Snake";
	static constexpr uint32_t UI_HUD_OFFSET_Y = 200;
	inline static const sf::Vector2u WINDOW_SIZE
	{
		sCellCountX * CELL_SIZE,
		sCellCountY * CELL_SIZE + UI_HUD_OFFSET_Y
	};

	// Настройки еды
	static const sf::Vector2f FOOD_SIZE;
	inline static int sPointsForFood = 2;

	// Настройки стены
	static const sf::Vector2f WALL_SIZE;

	// Настройки звуков
	static const float EAT_SOUND_VOLUME;
	static const float DEATH_SOUND_VOLUME;

	//Параметры крайних элементов поля
	inline static const sf::Vector2u sPositionOfLeftTopTile
	{
		0,
		0
	};
	inline static const sf::Vector2u sPositionOfRightTopTile
	{
		GameSettings::CELL_SIZE * (GameSettings::sCellCountX - 1),
		0
	};
	inline static const sf::Vector2u sPositionOfLeftBottomTile
	{
		0,
		GameSettings::CELL_SIZE * (GameSettings::sCellCountY - 1)
	};
	inline static const sf::Vector2u sPositionOfRightBottomTile
	{
		GameSettings::CELL_SIZE * (GameSettings::sCellCountX - 1),
		GameSettings::CELL_SIZE * (GameSettings::sCellCountY - 1)
	};
};
