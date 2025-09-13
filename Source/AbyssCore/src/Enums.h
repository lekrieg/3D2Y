//
// Created by lekrieg on 22/08/25.
//

#ifndef ENUMS_H
#define ENUMS_H

#include <vector>
#include <string>

namespace abyss
{
    namespace enums
    {
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

        enum class EntityTag
        {
            Default,
            Player,
            Enemy,
            SmallEnemy,
            Bullet,
            SpecialAttack1,
            Tile,
            Dangerous,
            Door,
            Npc,
            Unknown,
        };
        const char* EntityTagToString(EntityTag tag);
        EntityTag StringToEntityTag(const char *tag);
        std::vector<std::string> GetEntityTagNames();

        enum class ActionState
        {
            Default,
            Start,
            End
        };
    }
}

#endif //ENUMS_H
