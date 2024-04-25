#include "Food.h"
#include "GameSettings.h"

int Food::Collect()
{
	return GameSettings::GetGameDifficultySettings().scoreScale * GameSettings::POINTS_FOR_FOOD;
}

void Food::Respawn(const sf::Vector2u& position)
{
	SetPosition(position);
}
