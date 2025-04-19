#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../Entity.h"
#include "../EntityManager.h"
#include "../EntityTag.h"
#include "SFML/System/Vector2.hpp"
#include "Yaml.h"

#include <memory>

namespace abyss
{
	namespace serializer
	{
		class Serializer
		{
			private:

				EntityManager *m_entityManager = nullptr;

			public:

				inline Serializer(EntityManager *entityManager) : m_entityManager(entityManager)
				{
				}

				inline void serialize(YAML::Emitter &em)
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

				inline void Deserialize(YAML::Node nodes)
				{
					m_entityManager->Clear();

					for (auto node : nodes)
					{
						for (auto innerNode : node)
						{
							auto e =
								m_entityManager->AddEntity(abyss::StringToEntityTag(innerNode.first.Tag().c_str()));
							DeserializeTransform(innerNode, e);
						}
					}
				}

				inline void SerializeTransform(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
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

				inline void DeserializeTransform(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
				{
					if (auto data = node["TransformComponent"])
					{
						auto &t = e->AddComponent<abyss::components::Transform>();
						t.pos = data["pos"].as<sf::Vector2f>();
						t.scale = data["scale"].as<sf::Vector2f>();
					}
				}
		};
	}
}

#endif
