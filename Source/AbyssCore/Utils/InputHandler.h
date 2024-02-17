#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "../Math/Vector3D.h"
#include "Enums.h"
#include "../3rdParty/glfw/include/GLFW/glfw3.h"



namespace abyss
{
	namespace input
	{
		bool GetIsButtonDown(GLFWwindow* window, ABYSS_INPUT_BUTTON button);
		abyss::math::Vector3D GetMousePos(GLFWwindow* window);
	}
}

#endif