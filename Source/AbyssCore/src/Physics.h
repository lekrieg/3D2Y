#ifndef PHYSICS_H
#define PHYSICS_H

#include "Entity.h"

#include "components/Anim.h"
#include "components/BoundingBox.h"
#include "components/Transform.h"

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "Logger.h"

namespace abyss
{
	class Physics
	{
		public:

			sf::Vector2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
			{
				auto &aTransform = b->GetComponent<components::Transform>();
				auto &bTransform = a->GetComponent<components::Transform>();
				sf::Vector2f delta = sf::Vector2f(std::abs(bTransform.pos.x - aTransform.pos.x),
												  std::abs(bTransform.pos.y - aTransform.pos.y));

				auto &aHalfSize = a->GetComponent<components::BoundingBox>().halfSize;
				auto &bHalfSize = b->GetComponent<components::BoundingBox>().halfSize;

				sf::Vector2f overlap =
					sf::Vector2f(bHalfSize.x + aHalfSize.x - delta.x, bHalfSize.y + aHalfSize.y - delta.y);
				return overlap;
			}

			sf::Vector2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
			{
				auto &aTransform = b->GetComponent<components::Transform>();
				auto &bTransform = a->GetComponent<components::Transform>();
				sf::Vector2f delta = sf::Vector2f(std::abs(bTransform.previousPos.x - aTransform.previousPos.x),
												  std::abs(bTransform.previousPos.y - aTransform.previousPos.y));

				auto &aHalfSize = a->GetComponent<components::BoundingBox>().halfSize;
				auto &bHalfSize = b->GetComponent<components::BoundingBox>().halfSize;

				sf::Vector2f overlap =
					sf::Vector2f(bHalfSize.x + aHalfSize.x - delta.x, bHalfSize.y + aHalfSize.y - delta.y);
				return overlap;
			}

			bool IsInside(const abyss::math::Vec2<float> &pos, std::shared_ptr<Entity> e)
			{
				auto &anim = e->GetComponent<components::Anim>();
				auto &t = e->GetComponent<components::Transform>();

				sf::Vector2f halfSize = anim.animation.GetHalfSize();
				if ((pos.x < t.pos.x + halfSize.x && pos.x > t.pos.x - halfSize.x) &&
					(pos.y > t.pos.y - halfSize.y && pos.y < t.pos.y + halfSize.y))
				{
					return true;
				}

				return false;
			}

			// TODO: implements line intersect
			// TODO: implements entity intersect
			// I receive a and b + entity (wich have a position)
			// a is the player, b is the enemy
			// return bool indicating if it did intersect or no
			// need to do intersect with the bounding boxes from entities and see if there are some blocking
	};
}

#endif // !PHYSICS_H
