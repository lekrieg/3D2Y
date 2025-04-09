#ifndef CIRCLE_COLLISION_H
#define CIRCLE_COLLISION_H

#include "Component.h"

namespace core
{
	namespace components
	{
		class CircleCollision : public Component
		{
		public:
			float radius;

			CircleCollision() : CircleCollision(0)
			{

			}

			CircleCollision(float r) : radius(r)
			{
			}
		};
	}
}

#endif // !CIRCLE_COLLISION_H
