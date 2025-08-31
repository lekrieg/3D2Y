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
	m_app->GetFileNames().clear();
	m_app->GetUsedTextures().clear();
	m_app->GetSelectedSprite() = {};

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
	em << YAML::Key << s->GetId() << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "speed" << YAML::Value << s->speed;
	em << YAML::Key << "file_name" << YAML::Value << s->fileName;
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
			auto fileName = internalNode.second["file_name"].as<std::string>();
			if (m_app->GetFileNames()[fileName].empty())
			{
				m_app->GetFileName() = fileName;
				m_app->GetFileNames()[fileName] = fileName;
			}

			if (!m_app->GetUsedTextures()[fileName])
			{
				m_app->GetUsedTextures()[fileName] = std::make_shared<sf::Texture>();

				char* n = new char[fileName.size()];
				strcpy(n, fileName.c_str());
				int fileIndex = m_app->GetArchiver().GetFileIndex(n);

				archiver::ArchiveFileHeader* header = new archiver::ArchiveFileHeader;
				m_app->GetArchiver().GetFileHeaderInfoByIndex(fileIndex, header);
				char* buffer = new char[header->GetSize()];
				m_app->GetArchiver().GetFileData(fileIndex, buffer, header->GetSize());

				if (!m_app->GetUsedTextures()[fileName]->loadFromMemory(buffer, header->GetSize()))
				{
					ABYSS_ERROR("Failed to load texture!")
				}

				m_app->GetFilePath() = fileName;

				if (!m_app->GetRenderTexture().resize(m_app->GetUsedTextures()[fileName]->getSize()))
				{
					ABYSS_ERROR("Failed to resize render texture!")
				}

				delete[] n;
				delete[] buffer;
			}

			const auto& s = std::make_shared<SpriteAsset>(fileName);
			s->fileName = fileName;

			s->speed = internalNode.second["speed"].as<int>();
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
	em << YAML::Key << a->GetId() << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "file_name" << YAML::Value << a->fileName;
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
			audio->fileName = internalNode.second["file_name"].as<std::string>();
			audio->filePath = audio->fileName;

			audios.push_back(audio);
		}
	}
}

void Serializer::SerializeFont(YAML::Emitter &em, const std::shared_ptr<FontAsset>& f)
{
	em << YAML::BeginMap;
	em << YAML::Key << f->GetId() << YAML::Value << YAML::BeginMap;
	em << YAML::Key << "file_name" << YAML::Value << f->fileName;
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
			font->fileName = internalNode.second["file_name"].as<std::string>();
			font->filePath = font->fileName;

			fonts.push_back(font);
		}
	}
}
