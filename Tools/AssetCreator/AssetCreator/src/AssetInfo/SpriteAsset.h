//
// Created by lekrieg on 16/07/25.
//

#ifndef SPRITE_ASSET_H
#define SPRITE_ASSET_H

#include <memory>
#include <string>
#include <utility>

#include "Animation.h"
#include "BaseAsset.h"
#include "../Enums/SpriteType.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

namespace abyss
{
    namespace asset_info
    {
        class SpriteAsset : public BaseAsset
        {
        public:

            enums::SpriteType spriteType{};
            std::vector<std::shared_ptr<Animation>> animations{};
            int scale{};
            int speed{};

            std::shared_ptr<Animation> defaultFrame{std::make_shared<Animation>(sf::Vector2f(32.0f, 32.0f))};

            explicit SpriteAsset(std::string  path)
            {
                filePath = std::move(path);
            }

            void AddAnimation();
        };
    }
}

#endif //SPRITE_ASSET_H
