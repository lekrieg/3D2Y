#include "EntityTag.h"
#include <cstring>

const char* abyss::EntityTagToString(EntityTag tag)
{
	switch (tag)
	{
	case abyss::EntityTag::Default:
		return "Default";
	case abyss::EntityTag::Player:
		return "Player";
	case abyss::EntityTag::Enemy:
		return "Enemy";
	case abyss::EntityTag::SmallEnemy:
		return "SmallEnemy";
	case abyss::EntityTag::Bullet:
		return "Bullet";
	case abyss::EntityTag::SpecialAttack1:
		return "SpecialAttack1";
		break;
	case abyss::EntityTag::Tile:
		return "Tile";
		break;
	case abyss::EntityTag::Dangerous:
		return "Dangerous";
		break;
	case abyss::EntityTag::Unknown:
	default:
		return "Unknown";
	}
}

const abyss::EntityTag abyss::StringToEntityTag(const char* tag)
{
    if (strcmp(tag, "Default"))
    {
        return abyss::EntityTag::Default;
    }
    else if (strcmp(tag, "Player"))
    {
        return abyss::EntityTag::Player;
    }
    else if (strcmp(tag, "Enemy"))
    {
        return abyss::EntityTag::Enemy;
    }
    else if (strcmp(tag, "SmallEnemy"))
    {
        return abyss::EntityTag::SmallEnemy;
    }
    else if (strcmp(tag, "Bullet"))
    {
        return abyss::EntityTag::Bullet;
    }
    else if (strcmp(tag, "SpecialAttack1"))
    {
        return abyss::EntityTag::SpecialAttack1;
    }
    else if (strcmp(tag, "Tile"))
    {
        return abyss::EntityTag::Tile;
    }
    else if (strcmp(tag, "Dangerous"))
    {
        return abyss::EntityTag::Dangerous;
    }

    return abyss::EntityTag::Unknown;
}
