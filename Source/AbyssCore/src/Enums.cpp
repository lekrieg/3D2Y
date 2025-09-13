//
// Created by lekrieg on 22/08/25.
//

#include "Enums.h"

#include <map>

// Entity tag
const char *abyss::enums::EntityTagToString(const EntityTag tag)
{
    static const std::map<EntityTag, std::string> entityTagMap =
    {
        {EntityTag::Default, "Default"},
        {EntityTag::Player, "Player"},
        {EntityTag::Enemy, "Enemy"},
        {EntityTag::SmallEnemy, "SmallEnemy"},
        {EntityTag::Bullet, "Bullet"},
        {EntityTag::SpecialAttack1, "SpecialAttack1"},
        {EntityTag::Tile, "Tile"},
        {EntityTag::Dangerous, "Dangerous"},
        {EntityTag::Door, "Door"},
        {EntityTag::Npc, "Npc"},
        {EntityTag::Unknown, "Unknown"},
    };

    if (const auto it = entityTagMap.find(tag); it != entityTagMap.end())
    {
        return it->second.c_str();
    }

    return "Unknown";
}

abyss::enums::EntityTag abyss::enums::StringToEntityTag(const char *tag)
{
    static const std::map<std::string, EntityTag> entityTagMap =
    {
        {"Default", EntityTag::Default},
        {"Player", EntityTag::Player},
        {"Enemy", EntityTag::Enemy},
        {"SmallEnemy", EntityTag::SmallEnemy},
        {"Bullet", EntityTag::Bullet},
        {"SpecialAttack1", EntityTag::SpecialAttack1},
        {"Tile", EntityTag::Tile},
        {"Dangerous", EntityTag::Dangerous},
        {"Door", EntityTag::Door},
        {"Npc", EntityTag::Npc},
        {"Unknown", EntityTag::Unknown},
    };

    if (const auto it = entityTagMap.find(tag); it != entityTagMap.end())
    {
        return it->second;
    }

    return abyss::enums::EntityTag::Unknown;
}

std::vector<std::string> abyss::enums::GetEntityTagNames()
{
    std::vector<std::string> names;

    constexpr int maxSize = 11;
    for (int i = 0; i < maxSize; i++)
    {
        names.emplace_back(EntityTagToString(static_cast<EntityTag>(i)));
    }

    return names;
}

// Sprite type
const char *abyss::enums::SpriteTypeToString(const SpriteType tag)
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

abyss::enums::SpriteType abyss::enums::StringToSpriteType(const char *tag)
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

std::vector<std::string> abyss::enums::GetSpriteTypeNames()
{
    std::vector<std::string> names;

    constexpr int maxSize = 4;
    for (int i = 0; i < maxSize; i++)
    {
        names.emplace_back(SpriteTypeToString(static_cast<SpriteType>(i)));
    }

    return names;
}