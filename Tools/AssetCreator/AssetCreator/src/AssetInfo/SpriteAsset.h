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
#include "../Utils/SpriteType.h"

class SpriteAsset : public BaseAsset
{
public:

    SpriteType spriteType{};
    std::vector<std::shared_ptr<Animation>> animations{};
    int speed{};

    explicit SpriteAsset(std::string  path)
    {
        filePath = std::move(path);
    }

    void AddAnimation();
};

#endif //SPRITE_ASSET_H
