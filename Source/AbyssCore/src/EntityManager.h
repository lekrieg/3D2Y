#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

#include <memory>
#include <vector>
#include <map>

namespace abyss
{
	typedef std::vector<std::shared_ptr<Entity>> EntityVec;
	typedef std::map<enums::EntityTag, EntityVec> EntityMap;

	class EntityManager
	{
		EntityVec m_entities;
		EntityVec m_toAdd;
		EntityMap m_entityMap;
		size_t m_totalEntities = 0;

	public:
		EntityManager()
		{
		}

		void Update();
		std::shared_ptr<Entity> AddEntity(const enums::EntityTag& tag);
		EntityVec& GetEntities();
		EntityVec& GetEntities(const enums::EntityTag& tag);
		const std::map<enums::EntityTag, EntityVec>& GetEntityMap();
		void Clear();
		void UpdateEntityTag(const std::shared_ptr<abyss::Entity>& entity, const enums::EntityTag& newTag);

	private:
		void RemoveDeadEntities(EntityVec& vec);
	};
}

#endif // !ENTITY_MANAGER_H
