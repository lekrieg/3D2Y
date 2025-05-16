#include <cassert>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

class IComponentArray
{
	public:

		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(size_t entity) = 0;
};

template <typename T> class ComponentArray : public IComponentArray
{
	private:

		std::unordered_map<size_t, T> m_componentsMap;

	public:

		void AddComponent(size_t entity, T component)
		{
			m_componentsMap[entity] = component;
		}

		void RemoveComponent(size_t entity)
		{
			m_componentsMap.erase(entity);
		}

		T &GetComponent(size_t entity)
		{
			assert(m_componentsMap.count(entity) && "No component exist for this entity!");
			return m_componentsMap.at(entity);
		}

		void EntityDestroyed(size_t entity) override
		{
			RemoveComponent(entity);
		}

		bool Has(size_t entity)
		{
			return m_componentsMap.find(entity) != m_componentsMap.end();
		}
};
