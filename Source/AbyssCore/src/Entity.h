#ifndef ENTITY_H
#define ENTITY_H

#include "Enums.h"
#include <cstddef>


namespace abyss
{
	class EntityManager;

	class Entity
	{
		friend class EntityManager;

		size_t m_id = 0;
		size_t m_layer = 0;
		enums::EntityTag m_tag = enums::EntityTag::Default;
		bool m_alive = true;
		char m_name[255] = { "Default" };

	public:

		Entity(const enums::EntityTag& tag, size_t id) : m_tag(tag), m_id(id)
		{
		}

		void Destroy()
		{
			m_alive = false;
		}

		const enums::EntityTag Tag() const
		{
			return m_tag;
		}

		void SetTag(const enums::EntityTag& tag)
		{
			m_tag = tag;
		}

		bool IsActive() const
		{
			return m_alive;
		}

		const size_t Id() const
		{
			return m_id;
		}

		const size_t Layer() const
		{
			return m_layer;
		}

		void SetLayer(const size_t& newLayer)
		{
			m_layer = newLayer;
		}

		char* GetName()
		{
			return m_name;
		}
	};
}

#endif // !ENTITY_H
