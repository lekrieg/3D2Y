#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"

#include <vector>
#include <map>

namespace core
{
	typedef std::vector<std::shared_ptr<core::Entity>> EntityVec;
	typedef std::map<core::EntityTag, EntityVec> EntityMap;

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

	private:
		void RemoveDeadEntities(EntityVec& vec);
	};
}

#endif // !ENTITY_MANAGER_H
