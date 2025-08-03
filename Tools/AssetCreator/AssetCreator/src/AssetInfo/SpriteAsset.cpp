//
// Created by lekrieg on 30/07/25.
//

#include "SpriteAsset.h"

#include <memory>

void abyss::asset_info::SpriteAsset::AddAnimation()
{
    animations.push_back(std::make_shared<abyss::asset_info::Animation>(sf::Vector2f(32.0f, 32.0f)));
}
