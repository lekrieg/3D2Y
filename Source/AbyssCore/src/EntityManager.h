#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

#include <vector>
#include <map>

namespace abyss
{
	typedef std::vector<std::shared_ptr<abyss::Entity>> EntityVec;
	typedef std::map<abyss::EntityTag, EntityVec> EntityMap;

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
		std::shared_ptr<Entity> AddEntity(const EntityTag& tag);
		EntityVec& GetEntities();
		EntityVec& GetEntities(const EntityTag& tag);
		const std::map<EntityTag, EntityVec>& GetEntityMap();
		void Clear();

	private:
		void RemoveDeadEntities(EntityVec& vec);
	};
}

#endif // !ENTITY_MANAGER_H
