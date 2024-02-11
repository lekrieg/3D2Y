#include "InputHandler.h"

namespace abyss
{
	namespace input
	{
		std::vector<InputHandler*> InputHandler::m_instances;
		InputHandler::InputHandler() : m_isEnabled(true)
		{
			InputHandler::m_instances.push_back(this);
		}

		void InputHandler::InitializeInputs(GLFWwindow* window, std::vector<ABYSS_INPUT_BUTTON> buttonsToMonitor)
		{
			for(ABYSS_INPUT_BUTTON button : buttonsToMonitor)
			{
				m_buttons[button] = false;
			}

			glfwSetKeyCallback(window, InputHandler::Callback);
		}

		bool InputHandler::GetIsButtonDown(ABYSS_INPUT_BUTTON button)
		{
			bool result = false;
			if(m_isEnabled)
			{
				std::map<ABYSS_INPUT_BUTTON, bool>::iterator it = m_buttons.find(button);
				if(it != m_buttons.end())
				{
					result = m_buttons[button];
				}
			}

			return result;
		}

		abyss::math::Vector3D InputHandler::GetMousePos(GLFWwindow* window)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			abyss::math::Vector3D result(x, y, 0);
			return result;
		}

		void InputHandler::Callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			for (InputHandler* buttonInput : m_instances)
			{
				buttonInput->SetIsButtonDown(static_cast<ABYSS_INPUT_BUTTON>(key), action != GLFW_RELEASE);
			}
		}

		void InputHandler::SetIsButtonDown(ABYSS_INPUT_BUTTON button, bool isDown)
		{
			std::map<ABYSS_INPUT_BUTTON, bool>::iterator it = m_buttons.find(button);
			if(it != m_buttons.end())
			{
				m_buttons[button] = isDown;
			}
		}
	}
}