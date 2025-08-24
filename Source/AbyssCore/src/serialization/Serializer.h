#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../Assets.h"
#include "../Entity.h"
#include "../EntityManager.h"
#include "../Scene.h"
#include "Yaml.h"
#include "../assets/SpriteAsset.h"
#include "../assets/AudioAsset.h"

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
				Assets *m_assets = nullptr;

			public:

				Serializer(EntityManager *entityManager, ComponentManager *componentManager, Assets* assets) :
					m_entityManager(entityManager),
					m_componentManager(componentManager),
					m_assets(assets)
				{
				}

				void Serialize(YAML::Emitter &em);

				void Deserialize(YAML::Node nodes);
				void DeserializeAssets(YAML::Node nodes);

				void SerializeTransform(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeTransform(YAML::Node node, std::shared_ptr<abyss::Entity> &e);

				void SerializeAnim(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeAnim(YAML::Node node, std::shared_ptr<abyss::Entity> &e);

				void SerializeBoundingBox(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e);
				void DeserializeBoundingBox(YAML::Node node, std::shared_ptr<abyss::Entity> &e);

				void DeserializeSprite(const YAML::Node& node, std::map<std::string, assets::SpriteAsset>& sprites);
				void DeserializeAudio(const YAML::Node& node, std::map<std::string, assets::AudioAsset>& audios);
				void DeserializeFont(const YAML::Node& node, std::map<std::string, sf::Font>& fonts);
		};
	}
}

#endif
