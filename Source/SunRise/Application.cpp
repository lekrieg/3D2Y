#include "Application.h"

#include "Utils/Enums.h"

#include <iostream>
#include <vector>

bool Application::Initialize()
{
	ABYSS_RESULT result;

	m_params.name = "SunRise";
	m_params.isFullscreen = false;
	m_params.height = 600;
	m_params.width = 600;

	result = render.Initialize(&m_params, m_vertices);
	if(result != ABYSS_RESULT::ABYSS_SUCCESS)
	{
		return false;
	}

	result = render.CreateShaderFromFile({
		abyss::render::AbyssShader("C:/MyThings/Projects/git/3D2Y/Source/SunRise/Shaders/VertexShader.glsl", ABYSS_SHADER_TYPE::ABYSS_VERTEX_SHADER),
		abyss::render::AbyssShader("C:/MyThings/Projects/git/3D2Y/Source/SunRise/Shaders/FragmentShader.glsl", ABYSS_SHADER_TYPE::ABYSS_FRAGMENT_SHADER)
	});
	if(result != ABYSS_RESULT::ABYSS_SUCCESS)
	{
		return false;
	}

	return true;
}

void Application::Update()
{
	// TODO: Pega entrada do usuario
	if(abyss::input::GetIsButtonDown(m_params.window, ABYSS_INPUT_BUTTON::ABYSS_BUTTON_D))
	{
		std::cout << "D pressed!" << '\n';
	}

	// abyss::math::Vector3D test = inputHandler.GetMousePos(params.window);
	// std::cout << test.x << '\n';
}

void Application::Render()
{
	render.BeginRendering();
	render.ApplyShader();
	render.Render();

	render.EndRendering();
	//-----------------------------
	// TODO: limpa a tela
	// TODO: seta a view e rotaciona a matrix da camera
	// TODO: aplica o shader
	// TODO: aplica a textura
	// TODO: renderiza os modelos
}

void Application::Shutdown()
{
	render.Shutdown();
}

bool Application::ShouldCloseWindow()
{
	return render.ShouldCloseWindow();
}