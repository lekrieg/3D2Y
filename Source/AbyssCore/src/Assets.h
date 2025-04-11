#ifndef ASSETS_H
#define ASSETS_H

#include "Animation.h"
#include "FileData.h"
#include "soloud.h"
#include "soloud_wav.h"

#include <SFML/Graphics.hpp>
#include <map>

// TODO: MAKE THIS BECOME A RESOURCE MANAGER LIKE THE ONE FROM BUILDING BLOCKS ENGINE OR GAME ENGINE  DESIGN AND IMPLEMENTATION BOOKS
namespace abyss
{
	class Assets
	{
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, Animation> m_animations;
		std::map<std::string, std::string> m_sounds;
		std::map<std::string, sf::Font> m_fonts;

	public:

		void AddTexture(const TextureInfo& textureInfo);
		void AddAnimation(const AnimationInfo& animationInfo);
		void AddSound(const SoundInfo& soundInfo);
		void AddFont(const FontInfo& fontInfo);

		sf::Texture& GetTexture(std::string name);
		Animation& GetAnimation(std::string name);
		std::map<std::string, Animation>& GetAnimations();
		std::string& GetSound(std::string name);
		sf::Font& GetFont(std::string name);

		void LoadFromFile(std::string path);
	};
}

#endif // !ASSETS_H
