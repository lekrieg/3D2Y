#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../Assets.h"
#include "../Entity.h"
#include "../EntityManager.h"
#include "../Scene.h"
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
				ComponentManager *m_componentManager = nullptr;
				abyss::Assets m_assets;

			public:

				Serializer(EntityManager *entityManager, ComponentManager *componentManager,
						   const abyss::Assets &assets) :
					m_entityManager(entityManager),
					m_componentManager(componentManager),
					m_assets(assets)
				{
				}

				void Serialize(YAML::Emitter &em);

				void Deserialize(YAML::Node nodes);

				void SerializeTransform(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeTransform(YAML::Node node, std::shared_ptr<abyss::Entity> &e);

				void SerializeAnim(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeAnim(YAML::Node node, std::shared_ptr<abyss::Entity> &e);

				void SerializeBoundingBox(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeBoundingBox(YAML::Node node, std::shared_ptr<abyss::Entity> &e);
		};
	}
}

#endif
