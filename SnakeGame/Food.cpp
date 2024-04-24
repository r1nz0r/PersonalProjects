#include "Food.h"
#include "GameSettings.h"

int Food::Collect()
{
	return GameSettings::GetGameDifficultySettings().scoreScale;
}

void Food::Respawn(const sf::Vector2u& position)
{
	SetPosition(position);
}
