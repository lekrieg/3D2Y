//
// Created by lekrieg on 22/08/25.
//

#ifndef SPRITE_ASSET_H
#define SPRITE_ASSET_H

#include <map>

#include "../Enums.h"
#include "../Animation.h"

#include <memory>

#include "BaseAsset.h"

namespace abyss
{
    namespace assets
    {
        class SpriteAsset : public BaseAsset
        {
        public:

            enums::SpriteType spriteType{};
            int speed{};

            std::vector<std::string> animationNames;
            std::map<std::string, std::vector<sf::Vector2f>> sizes {};
            std::map<std::string, std::vector<sf::Vector2i>> positions {};
        };
    }
}

#endif //SPRITE_ASSET_H
