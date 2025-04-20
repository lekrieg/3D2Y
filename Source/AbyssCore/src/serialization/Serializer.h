#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../Entity.h"
#include "../EntityManager.h"
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

				Serializer(EntityManager *entityManager) : m_entityManager(entityManager)
				{
				}

				void Serialize(YAML::Emitter &em);

				void Deserialize(YAML::Node nodes);

				void SerializeTransform(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeTransform(YAML::Node node, std::shared_ptr<abyss::Entity> &e);
		};
	}
}

#endif
