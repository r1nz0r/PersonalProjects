#include "Walls.h"
#include "GameSettings.h"

void Wall::SetPosition(const sf::Vector2u& position)
{
    BaseEntity::SetPosition(position);
    OnPositionChanged(position);
}

void Wall::OnPositionChanged(const sf::Vector2u& position)
{
    sf::Vector2i tileSetPosition { 48, 8 };


    if (position == GameSettings::sPositionOfLeftTopTile || position == GameSettings::sPositionOfRightTopTile)
    {
        tileSetPosition = sf::Vector2i(96, 0);
    }
    else if (position == GameSettings::sPositionOfLeftBottomTile || position == GameSettings::sPositionOfRightBottomTile)
    {
        tileSetPosition = sf::Vector2i(104, 0);
    }
    else if (position.x == GameSettings::sPositionOfLeftBottomTile.x)
    {
        tileSetPosition = sf::Vector2i(64, 16);
    }
    else if (position.x == GameSettings::sPositionOfRightBottomTile.x)
    {
        tileSetPosition = sf::Vector2i(72, 16);
    }
    else if (position.y == GameSettings::sPositionOfRightTopTile.y)
    {
        tileSetPosition = sf::Vector2i(56, 16);
    }
    else if (position.y == GameSettings::sPositionOfRightBottomTile.y)
    {
        tileSetPosition = sf::Vector2i(80, 16);
    }

    SetTilePosition(tileSetPosition);
}

