#include "Serializer.h"

#include "../Assets.h"
#include "../EntityTag.h"
#include "SFML/System/Vector2.hpp"
#include "yaml-cpp/node/node.h"

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

			SerializeAnim(em, e);
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
		for (auto innerNode : node)
		{
			abyss::EntityTag tag = abyss::StringToEntityTag(innerNode.first.as<std::string>().c_str());
			auto e = m_entityManager->AddEntity(tag);

			YAML::Node components = innerNode.second;
			DeserializeAnim(components, e);
			DeserializeTransform(components, e);
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
		em << YAML::Key << "angle" << YAML::Value << t.angle;
		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeTransform(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["TransformComponent"])
	{
		auto &t = e->AddComponent<abyss::components::Transform>();
		t.pos = data["pos"].as<sf::Vector2f>();
		t.scale = data["scale"].as<sf::Vector2f>();
		t.angle = data["angle"].as<float>();
	}
}

void abyss::serializer::Serializer::SerializeAnim(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (e->HasComponent<abyss::components::Anim>())
	{
		auto &t = e->GetComponent<abyss::components::Anim>();
		em << YAML::Key << "AnimComponent";
		em << YAML::BeginMap;
		em << YAML::Key << "repeat" << YAML::Value << t.repeat;
		em << YAML::Key << "name" << YAML::Value << t.animation.GetName();
		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeAnim(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["AnimComponent"])
	{
		e->AddComponent<abyss::components::Anim>(m_assets.GetAnimation(data["name"].as<std::string>()),
												 data["repeat"].as<bool>());
	}
}

void abyss::serializer::Serializer::SerializeBoundingBox(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (e->HasComponent<abyss::components::BoundingBox>())
	{
		auto &t = e->GetComponent<abyss::components::BoundingBox>();
		em << YAML::Key << "BoundingBoxComponent";
		em << YAML::BeginMap;
		em << YAML::Key << "size" << YAML::Value << t.size;
		em << YAML::Key << "halfSize" << YAML::Value << t.halfSize;
		em << YAML::Key << "blockMove" << YAML::Value << t.blockMove;
		em << YAML::Key << "blockVision" << YAML::Value << t.blockVision;
		em << YAML::Key << "isTrigger" << YAML::Value << t.isTrigger;

		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeBoundingBox(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["BoundingBoxComponent"])
	{
		auto &t = e->AddComponent<abyss::components::BoundingBox>();
		t.size = data["size"].as<sf::Vector2f>();
		t.halfSize = data["halfSize"].as<sf::Vector2f>();
		t.blockMove = data["blockMove"].as<bool>();
		t.blockVision = data["blockVision"].as<bool>();
		t.isTrigger = data["isTrigger"].as<bool>();
	}
}
