#ifndef LIFESPAN_H
#define LIFESPAN_H

#include "Component.h"

namespace abyss
{
	namespace components
	{
		class Lifespan : public Component
		{
		public:
			int remaining;
			int total;

			Lifespan() : Lifespan(0)
			{

			}

			Lifespan(int t) : remaining(t), total(t)
			{
			}
		};
	}
}

#endif // !LIFESPAN_H
