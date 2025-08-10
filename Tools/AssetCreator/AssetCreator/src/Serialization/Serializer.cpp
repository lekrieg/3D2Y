#include "Serializer.h"

#include "SFML/System/Vector2.hpp"
#include "yaml-cpp/node/node.h"

void Serializer::Serialize(YAML::Emitter &em)
{
	em << YAML::BeginMap;

	em << YAML::Key << "Sprites" << YAML::Value << YAML::BeginSeq;
	for (const auto& s : m_app->GetSprites())
	{
		SerializeSprite(em, s);
	}
	em << YAML::EndSeq;

	em << YAML::Key << "Audios" << YAML::Value << YAML::BeginSeq;
	for (const auto& a : m_app->GetAudios())
	{
		SerializeAudio(em, a);
	}
	em << YAML::EndSeq;

	em << YAML::Key << "Fonts" << YAML::Value << YAML::BeginSeq;
	for (const auto& f : m_app->GetFonts())
	{
		SerializeFont(em, f);
	}
	em << YAML::EndSeq;

	em << YAML::EndMap;
}

void Serializer::Deserialize(const YAML::Node& nodes)
{
	if (auto spritesNode = nodes["Sprites"])
	{
		m_app->GetSprites().clear();
		DeserializeSprite(spritesNode, m_app->GetSprites());
	}

	if (auto audiosNode = nodes["Audios"])
	{
		m_app->GetAudios().clear();
		DeserializeAudio(audiosNode, m_app->GetAudios());
	}

	if (auto fontsNode = nodes["Fonts"])
	{
		m_app->GetFonts().clear();
		DeserializeFont(fontsNode, m_app->GetFonts());
	}
}

void Serializer::SerializeSprite(YAML::Emitter &em, const std::shared_ptr<SpriteAsset>& s)
{

	em << YAML::BeginMap;
	em << YAML::Key << s->assetName << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "speed" << YAML::Value << s->speed;
	em << YAML::Key << "scale" << YAML::Value << s->scale;
	em << YAML::Key << "file_path" << YAML::Value << s->filePath;
	em << YAML::Key << "sprite_type" << YAML::Value << SpriteTypeToString(s->spriteType);

	em << YAML::Key << "animations" << YAML::Value << YAML::BeginMap;
	auto& animations = s->animations;
	for (const auto& animation : animations)
	{
		em << YAML::Key << animation->name << YAML::Value << YAML::BeginMap;
		int frameIndex = 0;
		for (const auto& f : animation->frames)
		{
			em << YAML::Key << frameIndex << YAML::Value << YAML::BeginMap;
			em << YAML::Key << "size" << YAML::Value << f->size;
			em << YAML::Key << "pos" << YAML::Value << f->position;
			em << YAML::EndMap;

			frameIndex++;
		}
		em << YAML::EndMap;
	}

	em << YAML::EndMap;
	em << YAML::EndMap;
	em << YAML::EndMap;
}

void Serializer::DeserializeSprite(const YAML::Node& node, std::vector<std::shared_ptr<SpriteAsset>>& sprites)
{
	for (const auto& mainNode : node)
	{
		for (const auto& internalNode : mainNode)
		{
			auto filePath = internalNode.second["file_path"].as<std::string>();
			if (!m_app->GetUsedTextures()[filePath])
			{
				m_app->LoadTexture(filePath);
				m_app->GetUsedTextures()[std::move(filePath)] = std::make_shared<sf::Texture>(m_app->GetTexture());
			}

			const auto& s = std::make_shared<SpriteAsset>(filePath);
			auto sName = internalNode.first.as<std::string>();
			strcpy(s->assetName, sName.c_str());

			s->speed = internalNode.second["speed"].as<int>();
			s->scale = internalNode.second["scale"].as<float>();
			s->spriteType = StringToSpriteType(internalNode.second["sprite_type"].as<std::string>().c_str());

			for (const auto& animNode : internalNode.second["animations"])
			{
				const auto& anim = std::make_shared<Animation>();
				strcpy(anim->name,animNode.first.as<std::string>().c_str());

				for (const auto& frameNode : animNode.second)
				{
					auto size = frameNode.second["size"].as<sf::Vector2f>();
					auto pos = frameNode.second["pos"].as<sf::Vector2i>();

					const auto& frame = std::make_shared<Frame>(size, size / 2.0f, pos);
					anim->frames.push_back(frame);
				}

				s->animations.push_back(anim);
			}

			sprites.push_back(s);
		}
	}
}

void Serializer::SerializeAudio(YAML::Emitter &em, const std::shared_ptr<AudioAsset>& a)
{
	em << YAML::BeginMap;
	em << YAML::Key << a->assetName << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "file_path" << YAML::Value << a->filePath;
	em << YAML::EndMap;
	em << YAML::EndMap;
}

void Serializer::DeserializeAudio(const YAML::Node& node, std::vector<std::shared_ptr<AudioAsset>>& audios)
{
	for (const auto& audioNode : node)
	{
		for (const auto& internalNode : audioNode)
		{
			const auto audio = std::make_shared<AudioAsset>();
			strcpy(audio->assetName, internalNode.first.as<std::string>().c_str());
			audio->filePath = internalNode.second["file_path"].as<std::string>();

			audios.push_back(audio);
		}
	}
}

void Serializer::SerializeFont(YAML::Emitter &em, const std::shared_ptr<FontAsset>& f)
{
	em << YAML::BeginMap;
	em << YAML::Key << f->assetName << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "file_path" << YAML::Value << f->filePath;
	em << YAML::EndMap;
	em << YAML::EndMap;
}

void Serializer::DeserializeFont(const YAML::Node& node, std::vector<std::shared_ptr<FontAsset>>& fonts)
{
	for (const auto& audioNode : node)
	{
		for (const auto& internalNode : audioNode)
		{
			const auto font = std::make_shared<FontAsset>();
			strcpy(font->assetName, internalNode.first.as<std::string>().c_str());
			font->filePath = internalNode.second["file_path"].as<std::string>();

			fonts.push_back(font);
		}
	}
}
