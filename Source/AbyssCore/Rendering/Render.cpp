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

		// void OpenGLRenderer::ResizeWindow(float fov, float nearDist, float farDist, int width, int height)
		// {
		// 	glMatrixMode(GL_PROJECTION);
		// 	glLoadIdentity();
		// 	float aspectRatio = (float)width / (float)height;
		// 	float fH = tan(fov / 360.0 * M_PI) * nearDist;
		// 	float fW = fH * aspectRatio;
		// 	glFrustum(-fW, fW, -fH, fH, nearDist, farDist);
		// 	glMatrixMode(GL_MODELVIEW);
		// 	glLoadIdentity();
		// }

		// void OpenGLRenderer::ResizeWindowOrtho(int left, int right, int bottom, int top, float nearDist, float farDist)
		// {
		// 	glMatrixMode(GL_PROJECTION);
		// 	glLoadIdentity();
		// 	glFrustum(left, right, bottom, top, nearDist, farDist);
		// 	glMatrixMode(GL_MODELVIEW);
		// 	glLoadIdentity();
		// }

		// void OpenGLRenderer::SetClearColor(int r, int g, int b, int a)
		// {

		// }

		// void OpenGLRenderer::StartRendering(bool color, bool depth, bool stencil)
		// {

		// }

		void OpenGLRenderer::EndRendering()
		{
			glfwSwapBuffers(m_params.window);
			glfwPollEvents();
		}

		// ABYSS_RESULT OpenGLRenderer::Enable(ABYSS_RENDER_STATE state)
		// {

		// }

		// ABYSS_RESULT OpenGLRenderer::Disable(ABYSS_RENDER_STATE state)
		// {

		// }

		// void OpenGLRenderer::SetAlphaFunc(ABYSS_ALPHA_STATE state, float val)
		// {

		// }

		// void OpenGLRenderer::SetView(float posX, float posY, float posZ,
		// 			 float lookX, float lookY, float lookZ,
		// 			 float upX, float upY, float upZ)
		// {

		// }

		// void OpenGLRenderer::SetMatrix(const float *matrix)
		// {

		// }

		// void OpenGLRenderer::MultiplyToCurrentMatrix(const float *matrix)
		// {

		// }

		// ABYSS_RESULT OpenGLRenderer::SwitchMatrixType(ABYSS_MATRIX_TYPE type)
		// {

		// }

		// void OpenGLRenderer::GetMatrix(ABYSS_MATRIX_TYPE type, float *matrix)
		// {

		// }

		// void OpenGLRenderer::RotateMatrix(float angle, float x, float y, float z)
		// {

		// }

		// void OpenGLRenderer::TranslateMatrix(float x, float y, float z)
		// {

		// }

		// void OpenGLRenderer::LoadIdentityMatrix()
		// {

		// }

		// void OpenGLRenderer::PushMatrix()
		// {

		// }

		// void OpenGLRenderer::PopMatrix()
		// {


		// }

		// void OpenGLRenderer::ApplyFilters(ABYSS_TEXTURE &handle, ABYSS_FILTER_LIST_PTR filters)
		// {

		// }

		// bool OpenGLRenderer::AddEmptyTexture(char *name, int width, int height, int components,
		// 					 ABYSS_TEXTURE_TYPE type, ABYSS_TEXTURE_FORMAT format, ABYSS_TEXTURE *handle)
		// {

		// }

		// bool OpenGLRenderer::LoadTexFromFile(char *fileName, ABYSS_TEXTURE_TYPE type, ABYSS_TEXTURE *handle)
		// {

		// }

		// bool OpenGLRenderer::LoadTexFromMemory(char *name, char *fileData, int length, ABYSS_TEXTURE_TYPE type, ABYSS_TEXTURE *handle)
		// {

		// }

		// bool OpenGLRenderer::ApplyTexture(int texUnit, ABYSS_TEXTURE &handle)
		// {

		// }

		// void OpenGLRenderer::DeleteTexture(ABYSS_TEXTURE &handle)
		// {

		// }

		// bool OpenGLRenderer::CreateShaderFromFile(char *vs, char *ps, ShaderHandle *handle)
		// {

		// }

		// bool OpenGLRenderer::CreateShaderFromMemory(char *vsFile, char *psFile, ShaderHandle *handle)
		// {

		// }

		// void OpenGLRenderer::ApplyShader(ShaderHandle shader)
		// {

		// }

		// void OpenGLRenderer::SetupShaderParameter(char *pname, ShaderHandle shader, ParameterHandle *param)
		// {

		// }

		// void OpenGLRenderer::SetShaderParameter1i(ParameterHandle param, float val)
		// {

		// }

		// void OpenGLRenderer::SetShaderParameter1f(ParameterHandle param, float val)
		// {

		// }

		// void OpenGLRenderer::SetShaderParameter2f(ParameterHandle param, float x, float y)
		// {

		// }

		// void OpenGLRenderer::SetShaderParameter3f(ParameterHandle param, float x, float y, float z)
		// {

		// }

		// void OpenGLRenderer::SetShaderParameter4f(ParameterHandle param, float x, float y, float z, float w)
		// {

		// }
	}
}