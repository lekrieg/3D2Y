#include "EntityTag.h"

#include <map>
#include <string>

const char *abyss::EntityTagToString(const EntityTag tag)
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
        {EntityTag::Unknown, "Unknown"},
    };

    if (const auto it = entityTagMap.find(tag); it != entityTagMap.end())
    {
        return it->second.c_str();
    }

    return "Unknown";
}

abyss::EntityTag abyss::StringToEntityTag(const char *tag)
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
        {"Unknown", EntityTag::Unknown},
    };

    if (const auto it = entityTagMap.find(tag); it != entityTagMap.end())
    {
        return it->second;
    }

    return abyss::EntityTag::Unknown;
}

std::vector<std::string> abyss::GetEntityTagNames()
{
    std::vector<std::string> names;

    constexpr int maxSize = 9;
    for (int i = 0; i < maxSize; i++)
    {
        names.emplace_back(EntityTagToString(static_cast<EntityTag>(i)));
    }

    return names;
}
