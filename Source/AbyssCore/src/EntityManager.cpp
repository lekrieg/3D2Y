#include "EntityManager.h"
#include <algorithm>

void abyss::EntityManager::Update()
{
	for (auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->Tag()].push_back(e);
	}
	m_toAdd.clear();

	RemoveDeadEntities(m_entities);

	for (auto& pair : m_entityMap)
	{
		// first - tag
		// second - entity vec
		RemoveDeadEntities(pair.second);
	}

	if (m_shouldUpdateOrder)
	{
		std::sort(m_entities.begin(), m_entities.end(),
		  [](const std::shared_ptr<Entity> &lhs, const std::shared_ptr<Entity> &rhs)
		  {
			  return lhs->Layer() > rhs->Layer();
		  });

		m_shouldUpdateOrder = false;
	}
}

std::shared_ptr<abyss::Entity> abyss::EntityManager::AddEntity(const enums::EntityTag& tag)
{
	// TODO: check map edge cases
	auto e = std::make_shared<Entity>(tag, m_totalEntities++);
	m_toAdd.push_back(e);

	return e;
}

abyss::EntityVec& abyss::EntityManager::GetEntities()
{
	return m_entities;
}

abyss::EntityVec& abyss::EntityManager::GetEntities(const enums::EntityTag& tag)
{
	return m_entityMap[tag];
}

const std::map<abyss::enums::EntityTag, abyss::EntityVec>& abyss::EntityManager::GetEntityMap()
{
	return m_entityMap;
}

void abyss::EntityManager::RemoveDeadEntities(EntityVec& vec)
{
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity>& e) { return !e->IsActive();  }), vec.end());
}

void abyss::EntityManager::Clear()
{
    m_entities.clear();
    m_entityMap.clear();
    m_totalEntities = 0;
}

void abyss::EntityManager::UpdateEntityTag(const std::shared_ptr<abyss::Entity>& entity, const enums::EntityTag &newTag)
{
	auto& entityVec = m_entityMap[entity->Tag()];

	entityVec.erase(std::find(entityVec.begin(), entityVec.end(), entity));

	entity->SetTag(newTag);
	m_entityMap[newTag].push_back(entity);
}

void abyss::EntityManager::UpdateEntityLayer(const std::shared_ptr<abyss::Entity> &entity, size_t newLayer)
{
	m_shouldUpdateOrder = true;

	entity->SetLayer(newLayer);
}

void abyss::EntityManager::SortLayers()
{
	m_shouldUpdateOrder = true;
}
