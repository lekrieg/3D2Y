//
// Created by lekrieg on 16/07/25.
//

#ifndef SPRITE_TYPE_H
#define SPRITE_TYPE_H

#include <string>
#include <vector>

enum class SpriteType
{
    Prop,
    Building,
    Tile,
    Character,
};

const char* SpriteTypeToString(SpriteType tag);

SpriteType StringToSpriteType(const char *tag);

std::vector<std::string> GetSpriteTypeNames();

#endif //SPRITE_TYPE_H
