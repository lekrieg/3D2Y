#ifndef ENTITY_TAG_H
#define ENTITY_TAG_H

namespace abyss
{
	enum class EntityTag
	{
		Default,
		Player,
		Enemy,
		SmallEnemy,
		Bullet,
		SpecialAttack1,
		Tile,
		Dangerous,
	};

	const char* EntityTagToString(EntityTag tag);
}

#endif // !ENTITY_TAG_H
