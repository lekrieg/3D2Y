#ifndef STATE_H
#define STATE_H

#include "Component.h"
#include <string>

namespace abyss
{
	namespace components
	{
		class State : public Component
		{
		public:
			// TODO: Transformar essa porra em um enum, nao preciso desse objeto
			std::string state;

			State() : State("jumping")
			{

			}

			State(std::string state) : state(state)
			{

			}
		};
	}
}

#endif // !STATE_H
