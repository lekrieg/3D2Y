#ifndef ENTITY_H
#define ENTITY_H

#include "components/Transform.h"
#include "components/Input.h"
#include "components/Lifespan.h"
#include "components/BoundingBox.h"
#include "components/Anim.h"
#include "components/Gravity.h"
#include "components/State.h"
#include "components/Jump.h"
#include "components/Patrol.h"
#include "components/FollowPlayer.h"

#include "EntityTag.h"

#include <string>
#include <tuple>

namespace abyss
{
	class EntityManager;

	class Entity
	{
		friend class EntityManager;

		// TODO: Refactor this, there's no reason to keep wasting memory like this
		// maybe I could do a Component manager, that stores all related components in a vector
		// and this vector can be referenced using the entity id
		std::tuple<
			abyss::components::Transform,
			abyss::components::BoundingBox,
			abyss::components::Input,
			abyss::components::Lifespan,
			abyss::components::Anim,
			abyss::components::Gravity,
			abyss::components::State,
			abyss::components::Patrol,
			abyss::components::FollowPlayer,
			abyss::components::Jump> m_components;

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

		template <typename T>
		bool HasComponent() const
		{
			return GetComponent<T>().has;
		}

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			auto& component = GetComponent<T>();
			component = T(std::forward<TArgs>(args)...);
			component.has = true;

			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			return std::get<T>(m_components);
		}

		template<typename T>
		const T& GetComponent() const
		{
			return std::get<T>(m_components);
		}

		template<typename T>
		void RemoveComponent()
		{
			GetComponent<T>() = T();
		}
	};
}

#endif // !ENTITY_H
