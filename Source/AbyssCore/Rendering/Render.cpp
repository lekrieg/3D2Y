#include "Render.h"

#include <iostream>
#include <cstring>
#include <GL/gl.h>

namespace abyss
{
	namespace render
	{
		ABYSS_RESULT OpenGLRenderer::Initialize(const RenderParams *params)
		{
			ABYSS_RESULT result;

			if (params == nullptr)
			{
				return result;
			}
			memcpy(&m_params, params, sizeof(RenderParams));
			
			result = static_cast<ABYSS_RESULT>(glfwInit());
			if (result != ABYSS_RESULT::ABYSS_SUCCESS)
			{
				return result;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_params.window = glfwCreateWindow(m_params.width, m_params.height, m_params.name, nullptr, nullptr);
			if(m_params.window == nullptr)
			{
				std::cout << "Failed to create GLFW window" << '\n'; // TODO: use a log system
				result = ABYSS_RESULT::ABYSS_FAIL;
				return result;
			}
			glfwMakeContextCurrent(m_params.window);

			if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to intialize glad" << '\n'; // TODO: use a log system
				result = ABYSS_RESULT::ABYSS_FAIL;
				return result;
			}

			glfwSetWindowUserPointer ( m_params.window, this);
			glfwSetFramebufferSizeCallback(m_params.window, [](auto w, auto width, auto height)
			{
				auto render = reinterpret_cast<OpenGLRenderer*>(glfwGetWindowUserPointer(w));
				render->framebuffer_size_callback(width, height);
			});

			return ABYSS_RESULT::ABYSS_SUCCESS;
		}

		

		void OpenGLRenderer::Render(ABYSS_PRIMITIVE_TYPE type, VertexDescriptor *desc, char *vertexData,
					unsigned int *indices, int totalVertices, int totalIndices, int stride)
		{
			
		}

		void OpenGLRenderer::Shutdown()
		{
			glfwTerminate();
		}

		bool OpenGLRenderer::ShouldCloseWindow()
		{
			return glfwWindowShouldClose(m_params.window);
		}

		void OpenGLRenderer::SetViewPort(int x, int y, int width, int height)
		{
			glViewport(x, y, width, height);
		}

		void OpenGLRenderer::EndRendering()
		{
			glfwSwapBuffers(m_params.window);
			glfwPollEvents();
		}
	}
}