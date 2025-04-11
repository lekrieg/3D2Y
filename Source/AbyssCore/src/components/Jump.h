#ifndef JUMP_H
#define JUMP_H

#include "Component.h"

namespace abyss
{
	namespace components
	{
		class Jump : public Component
		{
		public:

			bool isJumping = false;
			float maxJumpTime;
			float jumpTime;

			Jump () : Jump(false, 0, 0)
			{

			}

			Jump (bool jumping, float actualTime, float maxAtualTime) : isJumping(jumping), jumpTime(actualTime), maxJumpTime(maxAtualTime)
			{

			}
		};
	}
}

#endif // !JUMP_H
