#ifndef ASSETS_H
#define ASSETS_H

#include "assets/SpriteAsset.h"
#include "assets/AudioAsset.h"
#include "assets/FontAsset.h"
#include "CustomSprite.h"
#include "archiver/FileArchiverHelper.h"

#include "soloud.h"
#include "soloud_wav.h"

#include <SFML/Graphics.hpp>
#include <map>

// TODO: MAKE THIS BECOME A RESOURCE MANAGER LIKE THE ONE FROM BUILDING BLOCKS ENGINE OR GAME ENGINE  DESIGN AND IMPLEMENTATION BOOKS
namespace abyss
{
	class Assets
	{
		archiver::Archive m_archive;

		std::map<std::string, sf::Texture> m_textures;
		std::map<int, assets::SpriteAsset> m_sprites;
		std::map<int, assets::AudioAsset> m_sounds;
		std::map<int, sf::Font> m_fonts;

		std::map<enums::SpriteType, std::vector<assets::SpriteAsset>> m_spritesPerType;

	public:

		Assets() = default;

		std::map<std::string, sf::Texture>& GetTextures();
		std::map<int, assets::SpriteAsset>& GetSprites();
		std::map<int, assets::AudioAsset>& GetAudios();
		std::map<int, sf::Font>& GetFonts();

		std::map<enums::SpriteType, std::vector<assets::SpriteAsset>>& GetSpritesPerType();

		archiver::Archive& GetArchiver();

		void LoadFromFile(const std::string& path);
	};
}

#endif // !ASSETS_H
