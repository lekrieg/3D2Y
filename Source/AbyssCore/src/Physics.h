#ifndef PHYSICS_H
#define PHYSICS_H

#include "Entity.h"

#include "Scene.h"
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

			sf::Vector2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b, ComponentManager* componentManager)
			{
				auto &aTransform = componentManager->GetComponent<components::Transform>(b->Id());
				auto &bTransform = componentManager->GetComponent<components::Transform>(a->Id());
				sf::Vector2f delta = sf::Vector2f(std::abs(bTransform.pos.x - aTransform.pos.x),
												  std::abs(bTransform.pos.y - aTransform.pos.y));

				auto &aHalfSize = componentManager->GetComponent<components::BoundingBox>(a->Id()).halfSize;
				auto &bHalfSize = componentManager->GetComponent<components::BoundingBox>(b->Id()).halfSize;

				sf::Vector2f overlap =
					sf::Vector2f(bHalfSize.x + aHalfSize.x - delta.x, bHalfSize.y + aHalfSize.y - delta.y);
				return overlap;
			}

			sf::Vector2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b, ComponentManager* componentManager)
			{
				auto &aTransform = componentManager->GetComponent<components::Transform>(b->Id());
				auto &bTransform = componentManager->GetComponent<components::Transform>(a->Id());
				sf::Vector2f delta = sf::Vector2f(std::abs(bTransform.previousPos.x - aTransform.previousPos.x),
												  std::abs(bTransform.previousPos.y - aTransform.previousPos.y));

				auto &aHalfSize = componentManager->GetComponent<components::BoundingBox>(a->Id()).halfSize;
				auto &bHalfSize = componentManager->GetComponent<components::BoundingBox>(b->Id()).halfSize;

				sf::Vector2f overlap =
					sf::Vector2f(bHalfSize.x + aHalfSize.x - delta.x, bHalfSize.y + aHalfSize.y - delta.y);
				return overlap;
			}

			bool IsInside(const abyss::math::Vec2<float> &pos, std::shared_ptr<Entity> e, ComponentManager* componentManager)
			{
				auto &anim = componentManager->GetComponent<components::Anim>(e->Id());
				auto &t = componentManager->GetComponent<components::Transform>(e->Id());

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
