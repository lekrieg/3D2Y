#ifndef ACTION_H
#define ACTION_H

#include "ActionState.h"

#include "math/Vectors.h"

#include <string>

namespace abyss
{
	class Action
	{
		std::string m_name;
		ActionState m_actionState;
		abyss::math::Vec2<int> m_position;

		public:

			Action() : Action("default", ActionState::Default)
			{
			}

			Action(const std::string &name, const ActionState &state) : Action(name, state, abyss::math::Vec2<int>())
			{
			}

			Action(const std::string &name, const ActionState &state, const abyss::math::Vec2<int> &pos) :
				m_name(name),
				m_actionState(state),
				m_position(pos)
			{
			}

			const std::string &Name() const
			{
				return m_name;
			}

			const ActionState &State() const
			{
				return m_actionState;
			}

			abyss::math::Vec2<int> Pos() const
			{
				return m_position;
			}
	};
}

#endif // !ACTION_H
