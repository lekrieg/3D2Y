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
}

std::shared_ptr<abyss::Entity> abyss::EntityManager::AddEntity(const EntityTag& tag)
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

abyss::EntityVec& abyss::EntityManager::GetEntities(const EntityTag& tag)
{
	return m_entityMap[tag];
}

const std::map<abyss::EntityTag, abyss::EntityVec>& abyss::EntityManager::GetEntityMap()
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

void abyss::EntityManager::UpdateEntityTag(const std::shared_ptr<abyss::Entity>& entity, const EntityTag &newTag)
{
	auto& entityVec = m_entityMap[entity->Tag()];

	entityVec.erase(std::find(entityVec.begin(), entityVec.end(), entity));

	entity->SetTag(newTag);
	m_entityMap[newTag].push_back(entity);
}
