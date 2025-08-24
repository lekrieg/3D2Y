//
// Created by lekrieg on 23/08/25.
//

#ifndef CUSTOM_SPRITE_H
#define CUSTOM_SPRITE_H

#include <algorithm>
#include <cstring>

#include "Enums.h"
#include "Animation.h"

#include <memory>

#include "assets/SpriteAsset.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace abyss
{
    class CustomSprite
    {
        private:

            sf::Sprite m_sprite;
            int m_currentFrame;
            int m_animFrame;

            std::shared_ptr<Animation> m_currentAnimation;

        public:

            std::string name;
            std::string path;

            enums::SpriteType spriteType{};
            std::vector<std::shared_ptr<Animation>> animations{};
            int speed{};

            CustomSprite(assets::SpriteAsset& spriteAsset, const sf::Texture &texture) : m_sprite(texture)
            {
                m_currentFrame = 0;
                m_animFrame = 0;

                this->path = path;

                name = spriteAsset.name;
                path = spriteAsset.path;

                spriteType = spriteAsset.spriteType;
                speed = spriteAsset.speed;

                for (const auto& animName : spriteAsset.animationNames)
                {
                    auto anim = std::make_shared<Animation>();
                    for (int i = 0; i < spriteAsset.sizes[animName].size(); i++)
                    {
                        anim->AddFrame(spriteAsset.sizes[animName][i], spriteAsset.positions[animName][i]);
                    }

                    animations.push_back(anim);
                }

                ConfigureDefaultAnimation();
            }

            void Update();
            bool HasEnded();

            void SetScale(const sf::Vector2<float> scale)
            {
            	m_sprite.setScale(scale);
            }

            void SetPosition(const sf::Vector2<float> pos)
            {
            	m_sprite.setPosition(pos);
            }

            void SetRotation(const float angle)
            {
            	m_sprite.setRotation(sf::degrees(angle));
            }

            sf::Sprite& GetSprite()
            {
                return m_sprite;
            }

            void SetAnimation(const std::string& animation)
            {
                m_currentAnimation = *std::find_if(animations.begin(), animations.end(), [&](const std::shared_ptr<Animation>& val){ return strcmp(val->name, animation.c_str()) == 0; });
            }

            const std::shared_ptr<Animation>& GetAnimation() const
            {
                return m_currentAnimation;
            }

            void ConfigureDefaultAnimation()
            {
                m_currentAnimation = animations[0];

                m_sprite.setOrigin(animations[0]->frames[0]->halfSize);
                m_sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(
                    m_currentAnimation->frames[0]->position.x,
                    m_currentAnimation->frames[0]->position.y),
                    sf::Vector2<int>(static_cast<int>(m_currentAnimation->frames[0]->size.x), static_cast<int>(m_currentAnimation->frames[0]->size.y))));
            }
    };
}

#endif //CUSTOM_SPRITE_H
