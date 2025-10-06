#include "Serializer.h"

#include "../Assets.h"
#include "../Enums.h"
#include "SFML/System/Vector2.hpp"
#include "../components/Anim.h"
#include "../components/BoundingBox.h"
#include "../components/Input.h"
#include "../components/Patrol.h"
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
		em << YAML::Key << enums::EntityTagToString(innerMap.first) << YAML::Value << YAML::BeginMap;

		int index = 0;
		for (auto &e : innerMap.second)
		{
			em << YAML::Key << index << YAML::Value << YAML::BeginMap;

			SerializeExtraData(em, e);
			SerializeAnim(em, e);
			SerializeTransform(em, e);
			SerializeBoundingBox(em, e);
			SerializeInput(em, e);
			SerializePatrol(em, e);

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
			enums::EntityTag tag = enums::StringToEntityTag(innerNode.first.as<std::string>().c_str());

			YAML::Node indexNode = innerNode.second;
			// index nodes
			for (auto comp : indexNode)
			{
				auto e = m_entityManager->AddEntity(tag);
				YAML::Node components = comp.second;
				DeserializeExtraData(components, e);
				DeserializeAnim(components, e);
				DeserializeTransform(components, e);
				DeserializeBoundingBox(components, e);
				DeserializeInput(components, e);
				DeserializePatrol(components, e);
			}
		}
	}
}

void abyss::serializer::Serializer::DeserializeAssets(YAML::Node nodes)
{
	if (auto spritesNode = nodes["Sprites"])
	{
		DeserializeSprite(spritesNode, m_assets->GetSprites());
	}

	if (auto audiosNode = nodes["Audios"])
	{
		DeserializeAudio(audiosNode, m_assets->GetAudios());
	}

	if (auto fontsNode = nodes["Fonts"])
	{
		DeserializeFont(fontsNode, m_assets->GetFonts());
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
		em << YAML::Key << "asset_id" << YAML::Value << t.animation.assetId;
		em << YAML::Key << "speed" << YAML::Value << t.animation.speed;
		em << YAML::Key << "should_draw" << YAML::Value << t.shouldDraw;
		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeAnim(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["AnimComponent"])
	{
		unsigned int assetId = data["asset_id"].as<unsigned int>();
		auto& s = m_assets->GetSprites()[assetId];
        m_componentManager->AddComponent<abyss::components::Anim>(e->Id(), abyss::components::Anim(CustomSprite(s, m_assets->GetTextures()[s.path]),
												 data["repeat"].as<bool>()));
        auto &anim = m_componentManager->GetComponent<abyss::components::Anim>(e->Id());
		anim.animation.speed = data["speed"].as<int>();
		anim.shouldDraw = data["should_draw"].as<bool>();
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

void abyss::serializer::Serializer::SerializeInput(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (m_componentManager->HasComponent<abyss::components::Input>(e->Id()))
	{
		em << YAML::Key << "InputComponent" << YAML::Value << YAML::BeginMap;
		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializeInput(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["InputComponent"])
	{
		m_componentManager->AddComponent<abyss::components::Input>(e->Id(), abyss::components::Input());
	}
}

void abyss::serializer::Serializer::SerializeExtraData(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	em << YAML::Key << "ExtraData" << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "name" << YAML::Value << e->GetName();
	em << YAML::Key << "layer" << YAML::Value << e->Layer();
	em << YAML::EndMap;
}

void abyss::serializer::Serializer::DeserializeExtraData(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["ExtraData"])
	{
		e->SetLayer(data["layer"].as<size_t>());
		strcpy(e->GetName(), data["name"].as<std::string>().c_str());
	}
}

void abyss::serializer::Serializer::SerializePatrol(YAML::Emitter &em, std::shared_ptr<abyss::Entity> e)
{
	if (m_componentManager->HasComponent<abyss::components::Patrol>(e->Id()))
	{
		auto &t = m_componentManager->GetComponent<abyss::components::Patrol>(e->Id());
		em << YAML::Key << "PatrolComponent" << YAML::Value << YAML::BeginMap;
		em << YAML::Key << "Positions" << YAML::Value << YAML::BeginMap;

		int index = 0;
		for (const auto& pos : t.positions)
		{
			em << YAML::Key << index << YAML::Value << sf::Vector2f(pos.x, pos.y);
			index++;
		}
		em << YAML::EndMap;

		em << YAML::Key << "speed" << YAML::Value << t.speed;

		em << YAML::EndMap;
	}
}

void abyss::serializer::Serializer::DeserializePatrol(YAML::Node node, std::shared_ptr<abyss::Entity> &e)
{
	if (auto data = node["PatrolComponent"])
	{
		m_componentManager->AddComponent<abyss::components::Patrol>(e->Id(), abyss::components::Patrol());
		auto &t = m_componentManager->GetComponent<abyss::components::Patrol>(e->Id());

		for (const auto& pos : data["Positions"])
		{
			const auto& internalPos = pos.second.as<sf::Vector2f>();
			t.positions.emplace_back(internalPos.x, internalPos.y);
		}

		t.speed = data["speed"].as<float>();
	}
}

void abyss::serializer::Serializer::DeserializeSprite(const YAML::Node& node, std::map<int, assets::SpriteAsset>& sprites)
{
	for (const auto& mainNode : node)
	{
		for (const auto& internalNode : mainNode)
		{
			auto fileName = internalNode.second["file_name"].as<std::string>();

			m_assets->GetTextures()[fileName] = sf::Texture();

			char* n = new char[fileName.size()];
			strcpy(n, fileName.c_str());
			int fileIndex = m_assets->GetArchiver().GetFileIndex(n);

			archiver::ArchiveFileHeader* header = new archiver::ArchiveFileHeader;
			m_assets->GetArchiver().GetFileHeaderInfoByIndex(fileIndex, header);
			char* buffer = new char[header->GetSize()];
			m_assets->GetArchiver().GetFileData(fileIndex, buffer, header->GetSize());

			if (!m_assets->GetTextures()[fileName].loadFromMemory(buffer, header->GetSize()))
			{
				ABYSS_ERROR("Failed to load texture!");
			}

			delete[] n;
			delete[] buffer;

			int id = internalNode.first.as<unsigned int>();
			auto s = assets::SpriteAsset();
			s.assetId = id;
			s.path = fileName;

			s.speed = internalNode.second["speed"].as<int>();
			s.spriteType = enums::StringToSpriteType(internalNode.second["sprite_type"].as<std::string>().c_str());

			for (const auto& animNode : internalNode.second["animations"])
			{
				std::string animationName = animNode.first.as<std::string>();
				s.animationNames.push_back(animationName);

				for (const auto& frameNode : animNode.second)
				{
					auto size = frameNode.second["size"].as<sf::Vector2f>();
					auto pos = frameNode.second["pos"].as<sf::Vector2i>();

					s.sizes[animationName].push_back(size);
					s.positions[animationName].push_back(pos);
				}
			}

			// PROBLEMA COM O NOME DAS ANIMACOES

			sprites[s.assetId] = s;

			m_assets->GetSpritesPerType()[s.spriteType].push_back(s);
		}
	}
}

void abyss::serializer::Serializer::DeserializeAudio(const YAML::Node& node, std::map<int, assets::AudioAsset>& audios)
{
	for (const auto& audioNode : node)
	{
		for (const auto& internalNode : audioNode)
		{
			int id = internalNode.first.as<unsigned int>();
			auto audio = assets::AudioAsset();
			audio.assetId = id;
			audio.path = internalNode.second["file_name"].as<std::string>();

			audios[audio.assetId] = audio;
		}
	}
}

void abyss::serializer::Serializer::DeserializeFont(const YAML::Node& node, std::map<int, sf::Font>& fonts)
{
	for (const auto& audioNode : node)
	{
		for (const auto& internalNode : audioNode)
		{
			int id = internalNode.first.as<unsigned int>();
			auto font = assets::FontAsset();
			font.assetId = id;
			font.path = internalNode.second["file_name"].as<std::string>();

			char* pathName = new char[font.path.size()];
			strcpy(pathName, font.path.c_str());

			int fileIndex = m_assets->GetArchiver().GetFileIndex(pathName);
			archiver::ArchiveFileHeader* header = new archiver::ArchiveFileHeader;
			m_assets->GetArchiver().GetFileHeaderInfoByIndex(fileIndex, header);

			char* buffer = new char[header->GetSize()];
			m_assets->GetArchiver().GetFileData(fileIndex, buffer, header->GetSize());

			fonts[font.assetId] = sf::Font(buffer, header->GetSize());
		}
	}
}