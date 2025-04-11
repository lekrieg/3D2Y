#ifndef GRAVITY_H
#define GRAVITY_H

#include "Component.h"

namespace abyss
{
	namespace components
	{
		class Gravity : public Component
		{
		public:
			float gravity;

			Gravity() : Gravity(0)
			{

			}

			Gravity(float g) : gravity(g)
			{

			}
		};
	}
}

#endif // !GRAVITY_H
