#ifndef ENTITY_H
#define ENTITY_H

#include "EntityTag.h"
#include <cstddef>


namespace abyss
{
	class EntityManager;

	class Entity
	{
		friend class EntityManager;

		size_t m_id = 0;
		const EntityTag m_tag = EntityTag::Default;
		bool m_alive = true;

	public:

		Entity(const EntityTag& tag, size_t id) : m_tag(tag), m_id(id)
		{
		}

		void Destroy()
		{
			m_alive = false;
		}

		const EntityTag Tag() const
		{
			return m_tag;
		}

		bool IsActive() const
		{
			return m_alive;
		}

		const size_t Id() const
		{
			return m_id;
		}
	};
}

#endif // !ENTITY_H
