#include "InputHandler.h"

namespace abyss
{
	namespace input
	{
		bool GetIsButtonDown(GLFWwindow *window, ABYSS_INPUT_BUTTON button)
		{
			return glfwGetKey(window, static_cast<int>(button)) == GLFW_PRESS;
		}

		abyss::math::Vector3D GetMousePos(GLFWwindow* window)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			abyss::math::Vector3D result(x, y, 0);
			return result;
		}
	}
}