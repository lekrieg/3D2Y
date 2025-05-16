#include "ComponentArray.h"
#include "Logger.h"
#include <cassert>
#include <cstddef>
#include <memory>
#include <string>
#include <sys/types.h>
#include <unordered_map>

class ComponentManager
{
	private:

		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> m_componentArrays {};

	public:

		template <typename T> void RegisterComponent()
		{
			std::string typeName = typeid(T).name();

			m_componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
		}

		template <typename T> void AddComponent(size_t entity, T component)
		{
			GetComponentArray<T>()->AddComponent(entity, component);
		}

		template <typename T> void RemoveComponent(size_t entity)
		{
			GetComponentArray<T>()->RemoveComponent(entity);
		}

		template <typename T> T &GetComponent(size_t entity)
		{
			return GetComponentArray<T>()->GetComponent(entity);
		}

		void EntityDestroyed(size_t entity)
		{
			for (auto &pair : m_componentArrays)
			{
				pair.second->EntityDestroyed(entity);
			}
		}

		template <typename T> bool HasComponent(size_t entity)
		{
			return GetComponentArray<T>()->Has(entity);
		}

	private:

		template <typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			std::string typeName = typeid(T).name();
			assert(m_componentArrays.count(typeName) && "No component registred!");
			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
		}
};
