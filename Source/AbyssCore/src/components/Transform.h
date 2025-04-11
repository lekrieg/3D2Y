#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

#include "SFML/System/Vector2.hpp"

namespace abyss
{
	namespace components
	{
		class Transform : public Component
		{
		public:
			sf::Vector2f pos = { 0, 0 };
			sf::Vector2f previousPos = { 0, 0 };
			sf::Vector2f velocity = { 0, 0 };
			sf::Vector2f scale = { 1, 1 };
			float angle = 0;

			Transform()
			{

			}

			Transform(const sf::Vector2f& p) : pos(p)
			{

			}

			Transform(const sf::Vector2f& position, const sf::Vector2f velocity, const sf::Vector2f& scale, float angle) : pos(position), previousPos(position), velocity(velocity), scale(scale), angle(angle)
			{
			}
		};
	}
}

#endif // !TRANSFORM_H
