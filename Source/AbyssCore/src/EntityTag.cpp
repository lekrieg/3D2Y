#include "EntityTag.h"

const char* core::EntityTagToString(EntityTag tag)
{
	switch (tag)
	{
	case core::EntityTag::Default:
		return "Default";
	case core::EntityTag::Player:
		return "Player";
	case core::EntityTag::Enemy:
		return "Enemy";
	case core::EntityTag::SmallEnemy:
		return "SmallEnemy";
	case core::EntityTag::Bullet:
		return "Bullet";
	case core::EntityTag::SpecialAttack1:
		return "SpecialAttack1";
		break;
	case core::EntityTag::Tile:
		return "Tile";
		break;
	case core::EntityTag::Dangerous:
		return "Dangerous";
		break;
	default:
		return "Unknown";
	}
}
