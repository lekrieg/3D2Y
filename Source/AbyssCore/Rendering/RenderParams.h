#ifndef RENDER_PARAMS_H
#define RENDER_PARAMS_H

#include "../3rdParty/glfw/include/GLFW/glfw3.h"

namespace abyss
{
	namespace render
	{
		class RenderParams
		{
		public:
			GLFWwindow *window;

			char* name;
			bool isFullscreen;
			int width, height;

			RenderParams() : isFullscreen(false), width(0), height(0) {}
		};
	}
}

#endif