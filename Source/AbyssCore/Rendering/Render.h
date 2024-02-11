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
		struct stTexture {};
		typedef utils::Handle<stTexture> ABYSS_TEXTURE;
		typedef int ShaderHandle;
		typedef int ParameterHandle;

		class OpenGLRenderer
		{
			VertexDescriptor *m_currentDesc;

			// abyss::utils::ResourceManager<GLTexture, ABYSS_TEXTURE> *m_texManager;

			// std::vector<GLSLShader> m_shaders;
			// std::vector<GLSLParameter> m_parameters;

			RenderParams m_params;

		public:
			OpenGLRenderer() {}
			~OpenGLRenderer() { Shutdown(); }

			// RENDER STUFF
			ABYSS_RESULT Initialize(const RenderParams* params);
			void Render(ABYSS_PRIMITIVE_TYPE type, VertexDescriptor *desc, char *vertexData,
						unsigned int *indices, int totalVertices, int totalIndices, int stride);
			void Shutdown();
			bool ShouldCloseWindow();
			void SetViewPort(int x, int y, int width, int height);
			void EndRendering();

		private:
			void framebuffer_size_callback(int width, int height)
			{
				SetViewPort(0, 0, width, height);
			}
		};
	}
}

#endif