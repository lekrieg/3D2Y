#ifndef INPUT_H
#define INPUT_H

#include "Component.h"

namespace core
{
	namespace components
	{
		class Input : public Component
		{
		public:
			// TODO: refactor this lol
			bool up = false;
			bool left = false;
			bool right = false;
			bool down = false;
			bool shoot = false;
			bool canShoot = true;
			bool canJump = true;

			int hitCounter = 0;

			Input()
			{
			}
		};
	}
}

#endif // !INPUT_H
