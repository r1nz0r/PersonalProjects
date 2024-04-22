#pragma once
#include "BaseEntity.h"

class Food : public BaseEntity
{
public:
	Food() = default;
	~Food() override = default;

	int Collect();
	void Respawn(const sf::Vector2u& position);
};
