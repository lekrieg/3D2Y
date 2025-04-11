#ifndef NAME_H
#define NAME_H

#include "Component.h"

#include <string>

namespace abyss
{
	namespace components
	{
		class Name : public Component
		{
		public:
			std::string name;

			Name() : Name("default")
			{

			}

			Name(const std::string& n) : name(n)
			{

			}
		};
	}
}

#endif // !NAME_H
