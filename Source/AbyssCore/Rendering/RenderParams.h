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
			int colorBits, depthBits, stencilBits;
			int maxCacheBytes, maxCacheIndices;

			RenderParams() : isFullscreen(false), width(0), height(0),
							 colorBits(0), depthBits(0), stencilBits(0),
							 maxCacheBytes(0), maxCacheIndices(0) {}
		};
	}
}

#endif