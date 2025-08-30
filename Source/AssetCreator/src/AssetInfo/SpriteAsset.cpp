//
// Created by lekrieg on 30/07/25.
//

#include "SpriteAsset.h"

#include <memory>

void SpriteAsset::AddAnimation()
{
    animations.push_back(std::make_shared<Animation>(sf::Vector2f(32.0f, 32.0f)));
}
