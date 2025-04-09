#ifndef FILE_DATA_H
#define FILE_DATA_H

#include "SFML/Graphics.hpp"

#include <iostream>

struct WindowInfo
{
	int width, height;
	int frameLimit;
	bool fullScreen;
};

struct FontInfo
{
	std::string fontPath;
	std::string fontName;
};

struct TextureInfo
{
	std::string texturePath;
	std::string textureName;
	int indexX;
	int indexY;
	int itemSize;
	int frameCount;
};

struct AnimationInfo
{
	std::string textureName;
	std::string animationName;
	float frameCount;
	float animationSpeed;

};

struct PlayerInfo
{
	sf::Vector2f gridLocation;
	sf::Vector2f boundingBoxSize;
	sf::Vector2f speed;
	float maxSpeed;
	float gravity;
	std::string bulletAnimation;
};

struct TileInfo
{
	std::string animationName;
	sf::Vector2f gridPos;
};

struct SoundInfo
{
	std::string soundName;
	std::string filePath;
};

#endif // !FILE_DATA_H
