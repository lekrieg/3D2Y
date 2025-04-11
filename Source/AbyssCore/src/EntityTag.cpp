#include "EntityTag.h"

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
	default:
		return "Unknown";
	}
}
