#ifndef RENDER_H
#define RENDER_H

#include "../3rdParty/glad/include/glad/glad.h"
#include "RenderParams.h"
#include "../Utils/Enums.h"
#include "../Utils/ResourceManager.h"
#include "../Utils/RenderDefines.h"
#include "VertexDescriptor.h"

#include <functional>
#include <cmath>

namespace abyss
{
	namespace render
	{
		// RESOURCE HANDLE STUFF
		struct AbyssShader
		{
		public:
			AbyssShader(char* s, ABYSS_SHADER_TYPE shaderType)
			{
				shaderFile = s;
				t = shaderType;
			}

			char* shaderFile;
			ABYSS_SHADER_TYPE t;
		};

		class OpenGLRenderer
		{
			RenderParams m_params;
			
			// TODO: Check if I really need to put this thing globally
			unsigned int m_VBOs[1];
			unsigned int m_VAOs[1];
			unsigned int m_shaderPrograms[1];

			ABYSS_RESULT CreateShaderFromMemory(const char* shaderFile, ABYSS_SHADER_TYPE t);

		public:
			OpenGLRenderer() {}
			~OpenGLRenderer() { Shutdown(); }

			// RENDER STUFF
			ABYSS_RESULT Initialize(RenderParams* params, float vertices[]);
			void Render();
			void Shutdown();
			bool ShouldCloseWindow();
			void SetViewPort(int x, int y, int width, int height);
			void BeginRendering();
			void EndRendering();

			ABYSS_RESULT CreateShaderFromFile(std::vector<AbyssShader> shaders);
			void ApplyShader();

		private:
			void framebuffer_size_callback(int width, int height)
			{
				SetViewPort(0, 0, width, height);
			}
		};
	}
}

#endif