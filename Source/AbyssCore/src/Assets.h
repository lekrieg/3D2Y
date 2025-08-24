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
		std::map<std::string, assets::SpriteAsset> m_sprites; // o problema ta aqui! nao posso ter mais de dois itens com o mesmo nome...
																				// ou arrumo um jeito de criar os sprites sem dependencia
		std::map<std::string, assets::AudioAsset> m_sounds;
		std::map<std::string, sf::Font> m_fonts;

	public:

		Assets() =default;

		std::map<std::string, sf::Texture>& GetTextures();
		std::map<std::string, assets::SpriteAsset>& GetSprites();
		std::map<std::string, assets::AudioAsset>& GetAudios();
		std::map<std::string, sf::Font>& GetFonts();

		archiver::Archive& GetArchiver();

		void LoadFromFile(const std::string& path);
	};
}

#endif // !ASSETS_H
