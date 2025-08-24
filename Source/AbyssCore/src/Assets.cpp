#include "Assets.h"

#include "Logger.h"
#include "SFML/System/Vector2.hpp"

#include <fstream>

#include "serialization/Serializer.h"

std::map<std::string, sf::Texture> & abyss::Assets::GetTextures()
{
	return m_textures;
}

std::map<std::string, abyss::assets::SpriteAsset> & abyss::Assets::GetSprites()
{
	return m_sprites;
}

// SoLoud wav dont stay on memory when it leaves the method, I am using string because of this
// TODO: adicionar musica para os leveis
std::map<std::string, abyss::assets::AudioAsset> & abyss::Assets::GetAudios()
{
	return m_sounds;
}

std::map<std::string, sf::Font> & abyss::Assets::GetFonts()
{
	return m_fonts;
}

std::map<abyss::enums::SpriteType, std::vector<abyss::assets::SpriteAsset>> & abyss::Assets::GetSpritesPerType()
{
	return m_spritesPerType;
}

archiver::Archive & abyss::Assets::GetArchiver()
{
	return m_archive;
}

void abyss::Assets::LoadFromFile(const std::string& path)
{
	ABYSS_INFO("Deserializing: %s", path.c_str());
	YAML::Node root;
	try
	{
		root = YAML::LoadFile(path);
	}
	catch (YAML::ParserException& e)
	{
		ABYSS_ERROR("Failed to deserialize scene!");
		return;
	}

	char dataFileName[] = "data.abyss";
	m_archive.ReadArchiveFile(dataFileName);

	serializer::Serializer(nullptr, nullptr, this).DeserializeAssets(root);

	m_archive.CloseArchive();
}
