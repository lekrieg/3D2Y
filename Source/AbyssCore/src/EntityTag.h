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
		Unknown,
	};

	const char* EntityTagToString(EntityTag tag);
	const EntityTag StringToEntityTag(const char* tag);
}

#endif // !ENTITY_TAG_H
