#include "Serializer.h"

#include "../Assets.h"
#include "../EntityTag.h"
#include "SFML/System/Vector2.hpp"
#include "../components/Anim.h"
#include "../components/BoundingBox.h"
#include "../components/Transform.h"
#include "yaml-cpp/node/node.h"

// TODO: fix loading yaml with the new structure
// TODO: delete entity when click on clone or the asset manager and dont let the entity drop when you dont want
// TODO: block movement when mouse inside UI

void abyss::serializer::Serializer::Serialize(YAML::Emitter &em)
{
	em << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

	for (auto &innerMap : m_entityManager->GetEntityMap())
	{
		em << YAML::BeginMap;
		em << YAML::Key << abyss::EntityTagToString(innerMap.first) << YAML::Value << YAML::BeginMap;

		int index = 0;
		for (auto &e : innerMap.second)
		{
			em << YAML::Key << index << YAML::Value << YAML::BeginMap;

			SerializeAnim(em, e);
			SerializeTransform(em, e);
			SerializeBoundingBox(em, e);

			em << YAML::EndMap; // index

			index++;
		}

		em << YAML::EndMap; // entity tag
		em << YAML::EndMap;
	}

	em << YAML::EndSeq;
}

void abyss::serializer::Serializer::Deserialize(YAML::Node nodes)
{
	m_entityManager->Clear();

	// entity nodes
	for (auto node : nodes)
	{
		// tag nodes
		for (auto innerNode : node)
		{
			abyss::EntityTag tag = abyss::StringToEntityTag(innerNode.first.as<std::string>().c_str());

			YAML::Node indexNode = innerNode.second;
			// index nodes
			for (auto comp : indexNode)
			{
				auto e = m_entityManager->AddEntity(tag);
				YAML::Node components = comp.second;
				DeserializeAnim(components, e);
				DeserializeTransform(components, e);
				DeserializeBoundingBox(components, e);
			}
		}
	}
}

void abyss::serializer::Serializer::SerializeTransform(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (m_componentManager->HasComponent<abyss::components::Transform>(e->Id()))
	{
		auto &t = m_componentManager->GetComponent<abyss::components::Transform>(e->Id());
		em << YAML::Key << "TransformComponent" << YAML::Value << YAML::BeginMap;
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
	    m_componentManager->AddComponent<abyss::components::Transform>(e->Id(), abyss::components::Transform());
		auto &t = m_componentManager->GetComponent<abyss::components::Transform>(e->Id());
		t.pos = data["pos"].as<sf::Vector2f>();
		t.scale = data["scale"].as<sf::Vector2f>();
		t.angle = data["angle"].as<float>();
	}
}

void abyss::serializer::Serializer::SerializeAnim(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
   	if (m_componentManager->HasComponent<abyss::components::Anim>(e->Id()))
	{
		auto &t = m_componentManager->GetComponent<abyss::components::Anim>(e->Id());
		em << YAML::Key << "AnimComponent" << YAML::Value << YAML::BeginMap;
		em << YAML::Key << "repeat" << YAML::Value << t.repeat;
		em << YAML::Key << "name" << YAML::Value << t.animation.GetName();
		em << YAML::Key << "speed" << YAML::Value << t.animation.speed;
		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeAnim(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["AnimComponent"])
	{
        m_componentManager->AddComponent<abyss::components::Anim>(e->Id(), abyss::components::Anim(m_assets.GetAnimation(data["name"].as<std::string>()),
												 data["repeat"].as<bool>()));
        auto &anim = m_componentManager->GetComponent<abyss::components::Anim>(e->Id());
		anim.animation.speed = data["speed"].as<int>();
	}
}

void abyss::serializer::Serializer::SerializeBoundingBox(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (m_componentManager->HasComponent<abyss::components::BoundingBox>(e->Id()))
	{
		auto &bb = m_componentManager->GetComponent<abyss::components::BoundingBox>(e->Id());
		em << YAML::Key << "BoundingBoxComponent" << YAML::Value << YAML::BeginMap;
		em << YAML::Key << "size" << YAML::Value << bb.size;
		em << YAML::Key << "halfSize" << YAML::Value << bb.halfSize;
		em << YAML::Key << "blockMove" << YAML::Value << bb.blockMove;
		em << YAML::Key << "blockVision" << YAML::Value << bb.blockVision;
		em << YAML::Key << "isTrigger" << YAML::Value << bb.isTrigger;

		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeBoundingBox(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["BoundingBoxComponent"])
	{
	    m_componentManager->AddComponent<abyss::components::BoundingBox>(e->Id(), abyss::components::BoundingBox());
        auto &bb = m_componentManager->GetComponent<abyss::components::BoundingBox>(e->Id());
		bb.size = data["size"].as<sf::Vector2f>();
		bb.halfSize = data["halfSize"].as<sf::Vector2f>();
		bb.blockMove = data["blockMove"].as<bool>();
		bb.blockVision = data["blockVision"].as<bool>();
		bb.isTrigger = data["isTrigger"].as<bool>();
	}
}
