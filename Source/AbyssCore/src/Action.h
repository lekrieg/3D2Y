#ifndef ACTION_H
#define ACTION_H

#include "Enums.h"

#include "math/Vectors.h"

#include <string>

namespace abyss
{
	class Action
	{
		private:

			std::string m_name;
			enums::ActionState m_actionState;
			abyss::math::Vec2<int> m_position;
			float m_scrollWheelDelta;

		public:

			Action() : Action("default", enums::ActionState::Default)
			{
			}

			Action(const std::string &name, const enums::ActionState &state) : Action(name, state, abyss::math::Vec2<int>())
			{
			}

			Action(const std::string &name, const enums::ActionState &state, const abyss::math::Vec2<int> &pos) :
				Action(name, state, pos, 0.0f)
			{
			}

			Action(const std::string &name, const enums::ActionState &state, const abyss::math::Vec2<int> &pos,
				   const float scrollWheelDelta) :
				m_name(name),
				m_actionState(state),
				m_position(pos),
				m_scrollWheelDelta(scrollWheelDelta)
			{
			}

			const std::string &Name() const
			{
				return m_name;
			}

			const enums::ActionState &State() const
			{
				return m_actionState;
			}

			abyss::math::Vec2<int> Pos() const
			{
				return m_position;
			}

			float ScrollWheelDelta() const
			{
				return m_scrollWheelDelta;
			}
	};
}

#endif // !ACTION_H
