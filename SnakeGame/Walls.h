#pragma once
#include <vector>
#include "BaseEntity.h"
#include "functional"

class Wall : public BaseEntity
{

public:
    Wall() = default;
    ~Wall() override = default;

public:
    virtual void SetPosition(const sf::Vector2u& position);

private:

    void OnPositionChanged(const sf::Vector2u& position);
};

