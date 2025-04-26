#include "Scene.h"

#include "serialization/Serializer.h"
#include "Logger.h"

#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include <fstream>

int abyss::Scene::Width() const
{
	return m_application->GetWindow().getSize().x;
}

int abyss::Scene::Height() const
{
	return m_application->GetWindow().getSize().y;
}

void abyss::Scene::DrawLine(sf::Vector2<float> p1, sf::Vector2f p2)
{
	std::array line = { sf::Vertex { p1 }, sf::Vertex { p2 } };

	m_application->GetWindow().draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}

void abyss::Scene::Serialize(const std::string &path)
{
	ABYSS_INFO("Serializing: %s", path.c_str());

	YAML::Emitter emitter;
	emitter << YAML::BeginMap;
	abyss::serializer::Serializer(&m_entityManager, m_application->GetAssets()).Serialize(emitter);
	emitter << YAML::EndMap;

	std::ofstream filepath(path);
	filepath << emitter.c_str();
}

bool abyss::Scene::Deserialize(const std::string &path)
{
	ABYSS_INFO("Deserializing: %s", path.c_str());
	YAML::Node root;
	try
	{
		root = YAML::LoadFile(path);
	}
	catch (YAML::ParserException e)
	{
		ABYSS_ERROR("Failed to deserialize scene!");
		return false;
	}

	if (auto entities = root["Entities"])
	{
		abyss::serializer::Serializer(&m_entityManager, m_application->GetAssets()).Deserialize(entities);
		return true;
	}

	return false;
}
