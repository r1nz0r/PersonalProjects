#include "Food.h"

int Food::Collect()
{
	return 1;
}

void Food::Respawn(const sf::Vector2u& position)
{
	SetPosition(position);
}
