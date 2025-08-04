//
// Created by lekrieg on 29/07/25.
//
#include "SpriteType.h"

#include <map>

const char *abyss::utils::SpriteTypeToString(const SpriteType tag)
{
    static const std::map<SpriteType, std::string> SpriteTypeMap =
    {
        {SpriteType::Building, "Building"},
        {SpriteType::Character, "Character"},
        {SpriteType::Prop, "Prop"},
        {SpriteType::Tile, "Tile"},
    };

    if (const auto it = SpriteTypeMap.find(tag); it != SpriteTypeMap.end())
    {
        return it->second.c_str();
    }

    return "Unknown";
}

abyss::utils::SpriteType abyss::utils::StringToSpriteType(const char *tag)
{
    static const std::map<std::string, SpriteType> SpriteTypeMap =
    {
        {"Building", SpriteType::Building},
        {"Character", SpriteType::Character},
        {"Prop", SpriteType::Prop},
        {"Tile", SpriteType::Tile},
    };

    if (const auto it = SpriteTypeMap.find(tag); it != SpriteTypeMap.end())
    {
        return it->second;
    }

    return SpriteType::Prop;
}

std::vector<std::string> abyss::utils::GetSpriteTypeNames()
{
    std::vector<std::string> names;

    constexpr int maxSize = 4;
    for (int i = 0; i < maxSize; i++)
    {
        names.emplace_back(SpriteTypeToString(static_cast<SpriteType>(i)));
    }

    return names;
}