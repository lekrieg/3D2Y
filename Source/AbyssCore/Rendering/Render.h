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
			int m_red, m_green, m_blue, m_alpha;
			bool m_multiTexSupport, m_cubeMapSupport;

			VertexDescriptor *m_currentDesc;
			bool m_vboSupport, m_fboSupport, m_glslSupport;
			GLuint m_vbo, m_ibo;

			// abyss::utils::ResourceManager<GLTexture, ABYSS_TEXTURE> *m_texManager;

			// std::vector<GLSLShader> m_shaders;
			// std::vector<GLSLParameter> m_parameters;

			RenderParams m_params;

		public:
			OpenGLRenderer() : m_red(0), m_green(0), m_blue(0), m_alpha(0), m_cubeMapSupport(false), m_multiTexSupport(false) {}
			~OpenGLRenderer() { Shutdown(); }

			// RENDER STUFF
			ABYSS_RESULT Initialize(const RenderParams* params);
			void Render(ABYSS_PRIMITIVE_TYPE type, VertexDescriptor *desc, char *vertexData,
						unsigned int *indices, int totalVertices, int totalIndices, int stride);
			void Shutdown();
			bool ShouldCloseWindow();
			void SetViewPort(int x, int y, int width, int height);
			void ResizeWindow(float fov, float nearDist, float farDist, int width, int height);
			void ResizeWindowOrtho(int left, int right, int bottom, int top, float nearDist, float farDist);
			void SetClearColor(int r, int g, int b, int a);
			void StartRendering(bool color, bool depth, bool stencil);
			void EndRendering();
			ABYSS_RESULT Enable(ABYSS_RENDER_STATE state);
			ABYSS_RESULT Disable(ABYSS_RENDER_STATE state);
			void SetAlphaFunc(ABYSS_ALPHA_STATE state, float val);
			void SetView(float posX, float posY, float posZ,
						 float lookX, float lookY, float lookZ,
						 float upX, float upY, float upZ);

			void SetMatrix(const float* matrix);
			void MultiplyToCurrentMatrix(const float* matrix);
			ABYSS_RESULT SwitchMatrixType(ABYSS_MATRIX_TYPE type);
			void GetMatrix(ABYSS_MATRIX_TYPE type, float* matrix);
			void RotateMatrix(float angle, float x, float y, float z);
			void TranslateMatrix(float x, float y, float z);
			void LoadIdentityMatrix();
			void PushMatrix();
			void PopMatrix();

			// TEXTURE STUFF
			void ApplyFilters(ABYSS_TEXTURE& handle, ABYSS_FILTER_LIST_PTR filters);
			bool AddEmptyTexture(char* name, int width, int height, int components,
								 ABYSS_TEXTURE_TYPE type, ABYSS_TEXTURE_FORMAT format, ABYSS_TEXTURE* handle);
			bool LoadTexFromFile(char* fileName, ABYSS_TEXTURE_TYPE type, ABYSS_TEXTURE *handle);
			bool LoadTexFromMemory(char* name, char* fileData, int length, ABYSS_TEXTURE_TYPE type, ABYSS_TEXTURE* handle);
			bool ApplyTexture(int texUnit, ABYSS_TEXTURE& handle);
			void DeleteTexture(ABYSS_TEXTURE& handle);

			// SHADER STUFF
			bool CreateShaderFromFile(char* vs, char* ps, ShaderHandle* handle);
			bool CreateShaderFromMemory(char* vsFile, char* psFile, ShaderHandle* handle);
			void ApplyShader(ShaderHandle shader);
			void SetupShaderParameter(char* pname, ShaderHandle shader, ParameterHandle* param);
			void SetShaderParameter1i(ParameterHandle param, float val);
			void SetShaderParameter1f(ParameterHandle param, float val);
			void SetShaderParameter2f(ParameterHandle param, float x, float y);
			void SetShaderParameter3f(ParameterHandle param, float x, float y, float z);
			void SetShaderParameter4f(ParameterHandle param, float x, float y, float z, float w);

		private:
			void framebuffer_size_callback(int width, int height)
			{
				SetViewPort(0, 0, width, height);
				// ResizeWindow(45.0f, 0.1f, 1000, width, height);
			}
		};
	}
}

#endif