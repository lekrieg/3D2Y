#include "Assets.h"

#include "Logger.h"
#include "SFML/System/Vector2.hpp"

#include <fstream>

void abyss::Assets::AddTexture(const TextureInfo &textureInfo)
{
	// if (!texture.loadFromFile(path, sf::IntRect(10, 10, 32, 32)))
	//  cada linha vai ter x,y, widht e height de cada item, se for uma animacao, vai ter o tamanho total dela
	//  a animacao se vira com a textura

	sf::Texture texture;

	if (!texture.loadFromFile(
			textureInfo.texturePath, false,
			sf::IntRect(
				sf::Vector2<int>(textureInfo.indexX * textureInfo.itemSize, textureInfo.indexY * textureInfo.itemSize),
				sf::Vector2<int>(textureInfo.itemSize * textureInfo.frameCount, textureInfo.itemSize))))
	{
		ABYSS_ERROR("Could not load texture!");
		exit(-1);
	}

	m_textures[textureInfo.textureName] = texture;
}

void abyss::Assets::AddAnimation(const AnimationInfo &animationInfo)
{
	Animation animation = Animation(animationInfo.animationName, GetTexture(animationInfo.textureName),
									animationInfo.frameCount, animationInfo.animationSpeed);
	m_animations[animationInfo.animationName] = animation;
}

void abyss::Assets::AddSound(const SoundInfo &soundInfo)
{
	m_sounds[soundInfo.soundName] = soundInfo.filePath;
}

void abyss::Assets::AddFont(const FontInfo &fontInfo)
{
	sf::Font font;

	if (!font.openFromFile(fontInfo.fontPath))
	{
		ABYSS_ERROR("Could not load font!");
		exit(-1);
	}

	m_fonts[fontInfo.fontName] = font;
}

sf::Texture &abyss::Assets::GetTexture(std::string name)
{
	return m_textures[name];
}

abyss::Animation &abyss::Assets::GetAnimation(std::string name)
{
	return m_animations[name];
}

std::map<std::string, abyss::Animation> &abyss::Assets::GetAnimations()
{
	return m_animations;
}

// SoLoud wav dont stay on memory when it leaves the method, I am using string because of this
// TODO: adicionar musica para os leveis

std::string &abyss::Assets::GetSound(std::string name)
{
	return m_sounds[name];
}

sf::Font &abyss::Assets::GetFont(std::string name)
{
	return m_fonts[name];
}

void abyss::Assets::LoadFromFile(std::string path)
{
	std::ifstream ifs(path, std::ifstream::in);

	TextureInfo textureInfo;
	AnimationInfo animationInfo;
	FontInfo fontInfo;
	SoundInfo soundInfo;

	std::string itemType;
	while (ifs.good())
	{
		ifs >> itemType;
		if (itemType.compare("Texture") == 0)
		{
			ifs >> textureInfo.textureName >> textureInfo.texturePath >> textureInfo.indexX >> textureInfo.indexY >>
				textureInfo.itemSize >> textureInfo.frameCount;
			AddTexture(textureInfo);
		}
		else if (itemType.compare("Animation") == 0)
		{
			ifs >> animationInfo.animationName >> animationInfo.textureName >> animationInfo.frameCount >>
				animationInfo.animationSpeed;
			AddAnimation(animationInfo);
		}
		else if (itemType.compare("Font") == 0)
		{
			ifs >> fontInfo.fontName >> fontInfo.fontPath;
			AddFont(fontInfo);
		}
		else if (itemType.compare("Sound") == 0)
		{
			ifs >> soundInfo.soundName >> soundInfo.filePath;
			AddSound(soundInfo);
		}
	}
}
