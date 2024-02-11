#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "../Math/Vector3D.h"
#include "Enums.h"
#include "../3rdParty/glfw/include/GLFW/glfw3.h"

#include <map>
#include <vector>
#include <algorithm>

namespace abyss
{
	namespace input
	{
		class InputHandler
		{
		private:
			std::map<ABYSS_INPUT_BUTTON, bool> m_buttons;
			bool m_isEnabled;

			static std::vector<InputHandler*> m_instances;
			static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

			void SetIsButtonDown(ABYSS_INPUT_BUTTON button, bool isDown);

		public:
			InputHandler();

			~InputHandler()
			{
				m_instances.erase(std::remove(m_instances.begin(), m_instances.end(), this), m_instances.end());
			}

			void InitializeInputs(GLFWwindow* window, std::vector<ABYSS_INPUT_BUTTON> buttonsToMonitor);

			bool GetIsButtonDown(ABYSS_INPUT_BUTTON button);
			abyss::math::Vector3D GetMousePos(GLFWwindow* window);

			bool GetIsEnabled() { return m_isEnabled; }
			void SetIsEnabled(bool value) { m_isEnabled = value; }
		};
	}
}

#endif