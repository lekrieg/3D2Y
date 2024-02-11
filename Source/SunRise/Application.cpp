#include "Application.h"

#include "Utils/Enums.h"

#include <iostream>
#include <vector>

bool Application::Initialize()
{
	bool result = false;

	params.name = "SunRise";
	params.isFullscreen = false;
	params.height = 600;
	params.width = 600;

	if(render.Initialize(&params) != ABYSS_RESULT::ABYSS_SUCCESS)
	{
		return false;
	}

	std::vector<ABYSS_INPUT_BUTTON> buttons = {
		ABYSS_INPUT_BUTTON::ABYSS_BUTTON_SPACE
	};

	inputHandler.InitializeInputs(params.window, buttons);

	// TODO: Limpa a tela com uma cor nova
	// TODO: Ativa shader
	// TODO: Ativa textura
	// TODO: Carrega a mesh de teste
	// TODO: Seta os filtros que vao ser usados na textura
	// TODO: Carrega a textura
	// TODO: Cria e seta o shader

	return true;
}

void Application::Update()
{
	// TODO: Pega entrada do usuario
	if(inputHandler.GetIsButtonDown(ABYSS_INPUT_BUTTON::ABYSS_BUTTON_D))
	{
		std::cout << "Space pressed!" << '\n';
	}

	// abyss::math::Vector3D test = inputHandler.GetMousePos(params.window);
	// std::cout << test.x << '\n';
}

void Application::Render()
{
	render.EndRendering();
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