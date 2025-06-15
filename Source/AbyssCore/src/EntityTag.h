#ifndef ENTITY_TAG_H
#define ENTITY_TAG_H

#include <string>
#include <vector>

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

	EntityTag StringToEntityTag(const char *tag);

	std::vector<std::string> GetEntityTagNames();
}

#endif // !ENTITY_TAG_H
