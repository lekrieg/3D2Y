#include "Render.h"

#include "../Utils/FileHelper.h"

#include <iostream>
#include <string>
#include <cstring>
#include <GL/gl.h>

namespace abyss
{
	namespace render
	{
		ABYSS_RESULT OpenGLRenderer::Initialize(RenderParams *params, float vertices[])
		{
			ABYSS_RESULT result;

			if (params == nullptr)
			{
				return result;
			}
			
			result = static_cast<ABYSS_RESULT>(glfwInit());
			if (result != ABYSS_RESULT::ABYSS_SUCCESS)
			{
				return result;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			params->window = glfwCreateWindow(params->width, params->height, params->name, nullptr, nullptr);
			if(params->window == nullptr)
			{
				std::cout << "Failed to create GLFW window" << '\n'; // TODO: use a log system
				result = ABYSS_RESULT::ABYSS_FAIL;
				return result;
			}
			glfwMakeContextCurrent(params->window);

			if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to intialize glad" << '\n'; // TODO: use a log system
				result = ABYSS_RESULT::ABYSS_FAIL;
				return result;
			}

			glfwSetWindowUserPointer ( params->window, this);
			glfwSetFramebufferSizeCallback(params->window, [](auto w, auto width, auto height)
			{
				auto render = reinterpret_cast<OpenGLRenderer*>(glfwGetWindowUserPointer(w));
				render->framebuffer_size_callback(width, height);
			});

			memcpy(&m_params, params, sizeof(RenderParams));
			
			glGenVertexArrays(sizeof(m_VAOs) / sizeof(unsigned int), m_VAOs);
			glGenBuffers(sizeof(m_VBOs) / sizeof(unsigned int), m_VBOs);

			glBindVertexArray(m_VAOs[0]);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			return ABYSS_RESULT::ABYSS_SUCCESS;
		}

		

		void OpenGLRenderer::Render()
		{
			for (size_t i = 0; i < sizeof(m_VAOs) / sizeof(unsigned int); i++)
			{
				glBindVertexArray(m_VAOs[i]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			
		}

		void OpenGLRenderer::Shutdown()
		{
			glDeleteVertexArrays(2, m_VAOs);
			glDeleteBuffers(2, m_VBOs);
			for (size_t i = 0; i < sizeof(m_shaderPrograms) / sizeof(unsigned int); i++)
			{
			glDeleteProgram(m_shaderPrograms[i]);
			}
			
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
			glfwPollEvents();
			glfwSwapBuffers(m_params.window);
		}

		void OpenGLRenderer::BeginRendering()
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		ABYSS_RESULT OpenGLRenderer::CreateShaderFromFile(std::vector<AbyssShader> shaders)
		{
			ABYSS_RESULT result = ABYSS_RESULT::ABYSS_SUCCESS;
			if(shaders.empty())
			{
				result = ABYSS_RESULT::ABYSS_FAIL;
			}

			abyss::utils::FileInputStream file;
			int fileSize = 0;
			char* fileData = nullptr;

			for(int i = 0; i < shaders.size(); i++)
			{
				file.OpenFile(shaders[i].shaderFile, ABYSS_FILE_TYPE::ABYSS_TEXT_FILE);
				fileSize = file.GetFileSize();
				
				if(fileSize < 1)
				{
					result = ABYSS_RESULT::ABYSS_FAIL;
					break;
				}

				fileData = new char[fileSize++];
				memset(fileData, 0, fileSize);

				file.Read(fileData, fileSize);

				ABYSS_RESULT result = CreateShaderFromMemory(fileData, shaders[i].t);

				delete[] fileData;
			}

			return result;
		}

		ABYSS_RESULT OpenGLRenderer::CreateShaderFromMemory(const char* shaderFile, ABYSS_SHADER_TYPE t)
		{
			ABYSS_RESULT result = ABYSS_RESULT::ABYSS_SUCCESS;
			if(shaderFile == nullptr)
			{
				result = ABYSS_RESULT::ABYSS_FAIL;
			}

			unsigned int shader;
			int success;
			char infoLog[512];

			if(t == ABYSS_SHADER_TYPE::ABYSS_VERTEX_SHADER)
			{
				shader = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(shader, 1, &shaderFile, nullptr);
				glCompileShader(shader);

				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
					result = ABYSS_RESULT::ABYSS_VERTEX_SHADER_FAIL;
					return result;
				}
			}
			else if(t == ABYSS_SHADER_TYPE::ABYSS_FRAGMENT_SHADER)
			{
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(shader, 1, &shaderFile, nullptr);
				glCompileShader(shader);

				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
					result = ABYSS_RESULT::ABYSS_FRAGMENT_SHADER_FAIL;
					return result;
				}
			}

			m_shaderPrograms[0] = glCreateProgram();
			glAttachShader(m_shaderPrograms[0], shader);
			glLinkProgram(m_shaderPrograms[0]);

			glGetProgramiv(m_shaderPrograms[0], GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(m_shaderPrograms[0], 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				result = ABYSS_RESULT::ABYSS_SHADER_FAIL;
				return result;
			}
			
			glDeleteShader(shader);
			return result;
		}

		void OpenGLRenderer::ApplyShader()
		{
			for (size_t i = 0; i < sizeof(m_shaderPrograms) / sizeof(unsigned int); i++)
			{
				glUseProgram(m_shaderPrograms[i]);
			}
		}
	}
}