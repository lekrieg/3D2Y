#include "Serializer.h"

#include "../EntityTag.h"
#include "../Logger.h"
#include "SFML/System/Vector2.hpp"

void abyss::serializer::Serializer::Serialize(YAML::Emitter &em)
{
	em << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

	for (auto &innerMap : m_entityManager->GetEntityMap())
	{
		em << YAML::BeginMap;
		em << YAML::Key << abyss::EntityTagToString(innerMap.first);

		for (auto &e : innerMap.second)
		{
			em << YAML::BeginMap;

			SerializeTransform(em, e);

			em << YAML::EndMap;
		}

		em << YAML::EndMap;
	}

	em << YAML::EndSeq;
}

void abyss::serializer::Serializer::Deserialize(YAML::Node nodes)
{
	m_entityManager->Clear();

	for (auto node : nodes)
	{
		ABYSS_INFO("Entrei no primeiro loop!");
		for (auto innerNode : node)
		{
			ABYSS_INFO("Entrei no segundo loop!");
			auto e = m_entityManager->AddEntity(abyss::StringToEntityTag(innerNode.first.as<std::string>().c_str()));
			DeserializeTransform(innerNode, e);
		}
	}
}

void abyss::serializer::Serializer::SerializeTransform(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (e->HasComponent<abyss::components::Transform>())
	{
		auto &t = e->GetComponent<abyss::components::Transform>();
		em << YAML::Key << "TransformComponent";
		em << YAML::BeginMap;
		em << YAML::Key << "pos" << YAML::Value << t.pos;
		em << YAML::Key << "scale" << YAML::Value << t.scale;
		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeTransform(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	for (auto n : node)
	{
		ABYSS_INFO("Deserializando!");
		if (auto data = n["TransformComponent"])
		{
			ABYSS_INFO("No comeco do if!");
			auto &t = e->AddComponent<abyss::components::Transform>();
			ABYSS_INFO("Deserializei o transform!");
			t.pos = data["pos"].as<sf::Vector2f>();
			ABYSS_INFO("Peguei a pos!");
			t.scale = data["scale"].as<sf::Vector2f>();
			ABYSS_INFO("Peguei a scale!");
		}
	}
}
